//
// Created by thauvi_a on 5/29/17.
//


#include "server.h"

void 	f_names(t_client *clt, t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    if (clt->chan && tmp->chan)
    {
      dprintf(clt->fd, "%s", tmp->nickname);
      if (strcmp(tmp->nickname, "Anonymous-") == 0)
	dprintf(clt->fd, "%d\r\n", tmp->fd);
    }
    tmp = tmp->next;
  }
  //todo: segfault lors de 2 clients pas dans le même channel
}

void 	f_msg(t_client *clt, t_serv *serv)
{
  (void)clt;
  (void)serv;
}

void 	f_send_file(t_client *clt, t_serv *serv)
{
  (void)clt;
  (void)serv;
}

void 	f_accept_file(t_client *clt, t_serv *serv)
{
  (void)clt;
  (void)serv;
}

void	print_at_all(t_client *clt, t_serv *serv)
{
  t_client	*tmp;
  int 		i;

  i = 0;
  if (!clt->chan) {
    dprintf(clt->fd, "You are in any channel.\r\n");
    return ;
  }
  tmp = serv->head->next;
  while (tmp)
  {
    if (tmp->fd != clt->fd)
    {
       if (tmp->chan) {
	 if (strcmp(clt->chan->name, tmp->chan->name) == 0) {

	   dprintf(tmp->fd, "[%s] %s", tmp->chan->name, clt->nickname);
	   if (strcmp(clt->nickname, "Anonymous-") == 0)
	     dprintf(tmp->fd, "%d: ", clt->fd);
	   else
	     dprintf(tmp->fd, ": ");
	   while (clt->cmd[i]) {
	     dprintf(tmp->fd, "%s", clt->cmd[i]);
	     i++;
	     if (clt->cmd[i] == NULL)
	       dprintf(tmp->fd, "\r\n");
	     else
	       dprintf(tmp->fd, " ");
	   }
	 }
       }
    }
    tmp = tmp->next;
  }
}