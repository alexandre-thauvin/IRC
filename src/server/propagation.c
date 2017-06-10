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

int	find_empty(t_chan **tab)
{
  unsigned int		i;

  i = 0;
  while (i < 10)
  {
    if (!tab[i])
      return (i);
    i++;
  }
  return (-1);
}

void 		propag_join(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = serv->head->next;
  (void)serv;
  while (tmp)
  {
      if (tmp->chan)
      {
	if (strcmp(clt->chan[10]->name, tmp->chan[10]->name) == 0)
	  dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, clt->chan[10]->name);
      }
    tmp = tmp->next;
  }
}


void 		propag_part(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = clt;
  (void)serv;
  while (tmp)
  {
      if (check_chan(tmp))
	dprintf(tmp->fd, ":%s leave the channel : "
	 "%s\r\n", clt->nickname, clt->cmd[1]);
    tmp = tmp->next;
  }
}
