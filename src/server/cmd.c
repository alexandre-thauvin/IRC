//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"


void 	f_nick(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1])
  {
    if ((clt->nickname = malloc(30 * sizeof(char))) == NULL)
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
  //todo: else: lire la rfc pour savoir si substring...
}
void 		f_join(t_client *clt, t_serv *serv)
{
  t_chan	*tmp;

  tmp = find_chan(serv->ch_head, clt->cmd[1]);
  if (tmp  == NULL)
  {
    clt->chan = add_chan(serv->ch_head, clt->cmd[1], serv);
    dprintf(clt->fd, "Channel created:  %s\r\n", clt->cmd[1]);
    dprintf(clt->fd, "You joined the channel: %s\r\n", clt->cmd[1]);
    clt->chan->nb_users += 1;
  }
  else
  {
    clt->chan = tmp;
    dprintf(clt->fd, "You joined the channel %s\r\n", tmp->name);
    tmp->nb_users += 1;
  }
}

void 	f_part(t_client *clt, t_serv *serv)
{
  printf("arg: %s\n", clt->cmd[1]);
  printf("name: %s\n", clt->chan->name);
  if (strcmp(clt->cmd[1], clt->chan->name) == 0)
  {
    clt->chan->nb_users -= 1;
    if (clt->chan->nb_users == 0)
    {
      dprintf(clt->fd, "Deleted channel: %s\n", clt->chan->name);
      dprintf(clt->fd, "Please choose a channel.\r\n");
      dlt_chan(serv->ch_head, clt->cmd[1]);
    }
  }
  else
    dprintf(clt->fd, "BAD CHAN LOLOLOLOL\r\n");
  (void)serv;
}

void 	f_users(t_client *clt, t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    dprintf(clt->fd, "%s\r\n", tmp->nickname);
    tmp = tmp->next;
  }
  clt->nickname = clt->nickname;
}

void	f_quit(t_client *clt, t_serv *serv)
{
  t_client *tmp;

  (void) clt;
  tmp = serv->head->next;
  while (tmp)
  {
    close (tmp->fd);
    tmp = tmp->next;
  }
  close(serv->head->fd);
}