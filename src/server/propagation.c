/*
** propagation.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:09:13 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:09:14 2017 Alexandre Thauvin
*/

#include "server.h"

void 		propag_join(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
      if (tmp->chan)
      {
	if (strcmp(clt->chan->name, tmp->chan->name) == 0)
	  dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, clt->chan->name);
      }
    tmp = tmp->next;
  }
}

/*
void 		propag_part(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    if (tmp->chan)
    {
      if (strcmp(clt->chan->name, tmp->chan->name) == 0)
	//todo: dprintf du part
    }
    tmp = tmp->next;
  }
}*/
