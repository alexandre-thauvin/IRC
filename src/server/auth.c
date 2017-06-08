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
      if (strcmp(tmp->chan->name, clt->chan->name) == 0)
	dprintf(clt->fd, "%s\r\n", clt->nickname);
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
	   dprintf(tmp->fd, "[%s] %s: ", tmp->chan->name, clt->nickname);
	   dprintf(tmp->fd, "%s\r\n", clt->cmd[0]);
	 }
       }
    }
    tmp = tmp->next;
  }
}