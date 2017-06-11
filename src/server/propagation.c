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

int 	find_it(t_client *clt, char *name)
{
  int 		i;

  i = 0;

  while (clt->chan[i] && (strcmp(clt->chan[i]->name, name) != 0) && i < 10)
    i++;
  return (i);
}

int	find_empty(t_chan **tab)
{
  unsigned int		i;

  i = 0;
  while (i < 10)
  {
    if (tab[i] == NULL)
      return (i);
    i++;
  }
  return (-1);
}

void 		propag_join(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
      if (tmp->chan[10] && clt->chan[10])
      {
	if (strcmp(clt->chan[10]->name, tmp->chan[10]->name) == 0)
	  dprintf(tmp->fd, ":%s JOIN : %s\r\n", clt->nickname, clt->chan[10]->name);
      }
    tmp = tmp->next;
  }
}


void 		propag_part(t_serv *serv, t_client *clt)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
      if (check_chan(tmp))
	dprintf(tmp->fd, ":%s leave the channel : "
	 "%s\r\n", clt->nickname, clt->cmd[1]);
    tmp = tmp->next;
  }
}

void 		propag_quit(t_serv *serv, t_client *clt)
{
  t_client	*tmp;
  int 		i;

  i = 0;
  tmp = serv->head->next;
  while (clt->chan[i])
  {
    while (tmp)
    {
      if (check_chan(tmp))
	dprintf(tmp->fd, ":%s leave the channel : "
	 "%s\r\n", clt->nickname, clt->cmd[1]);
      tmp = tmp->next;
    }
    i++;
  }
}
