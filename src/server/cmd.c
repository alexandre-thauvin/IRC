//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"


void 	f_nick(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1])
  {
    dprintf(clt->fd, ":%s NICK %s\r\n", clt->nickname, clt->cmd[1]);
    if ((clt->nickname = malloc((strlen(clt->cmd[1]) + 1) * sizeof(char))) == NULL)
      quit_error(serv);
    clt->nickname = strcpy(clt->nickname, clt->cmd[1]);
  }
  else
    dprintf(clt->fd, "Bad command\r\n");
  serv->head = serv->head;
}

void 	f_list(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1] == NULL)
    aff_chan(serv->ch_head, clt->fd);
}
void 		f_join(t_client *clt, t_serv *serv)
{
  t_chan	*tmp;

  if (clt->cmd)
  {
    if (clt->cmd[1][0] == '#')
    {
      tmp = find_chan(serv->ch_head, clt->cmd[1]);
      if (tmp == NULL)
      {
	clt->chan = add_chan(serv->ch_head, clt->cmd[1], serv);
	clt->chan->nb_users += 1;
      } else {
	clt->chan = tmp;
	tmp->nb_users += 1;
      }
      dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, clt->cmd[1]);
    }
    else
      dprintf(clt->fd, "403 %s %s :Invalid channel name\r\n", clt->nickname, clt->cmd[1]);
  }
  else
  dprintf(clt->fd, "421 Wrong Command\r\n");
}

void 	f_part(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1]) {
    if (clt->chan) {
      if (strcmp(clt->cmd[1], clt->chan->name) == 0) {
	clt->chan->nb_users -= 1;
	if (clt->chan->nb_users == 0) {
	  dprintf(clt->fd, "Deleted channel: %s\n", clt->chan->name);
	  dprintf(clt->fd, "Please choose a channel.\r\n");
	  dlt_chan(serv->ch_head, clt->cmd[1]);
	}
      } else
	dprintf(clt->fd, "BAD CHAN LOLOLOLOL\r\n");
    }
    else
      dprintf(clt->fd, "You are in any chan\r\n");
  }
  else
    dprintf(clt->fd, "Missing argument\r\n");

  (void)serv;
}

void 	f_users(t_client *clt, t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    dprintf(clt->fd, "%s", tmp->nickname);
    if (strcmp(tmp->nickname, "Anonymous-") == 0)
      dprintf(clt->fd, "%d", tmp->fd);
    tmp = tmp->next;
    if (tmp)
      dprintf(clt->fd, "\n");
    else
      dprintf(clt->fd, "\r\n");
  }
  clt->nickname = clt->nickname;
}

void	f_quit(t_client *clt, t_serv *serv)
{
  (void)serv;
  close (clt->fd);
  dltFromChain(clt, clt->fd);
}