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

  tmp = serv->head->next;
  while (tmp)
  {
    if (tmp->fd != clt->fd)
      dprintf(tmp->fd, "%s\r\n", clt->cmd[0]);
    tmp = tmp->next;
  }
}