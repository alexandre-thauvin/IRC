/*
** more.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun Jun 11 15:12:08 2017 Alexandre Thauvin
** Last update Sun Jun 11 15:12:13 2017 Alexandre Thauvin
*/

#include "server.h"

int 		ret_u(t_client *tmp)
{
  int	u;

  u = 0;
  while (tmp->cmd[u] != NULL)
    u++;
  return (u);
}

void		print_nick(t_client *clt, t_serv *serv)
{
    dprintf(clt->fd, ":%s NICK %s\r\n", clt->nickname, clt->cmd[1]);
    if ((clt->nickname = malloc((strlen(clt->cmd[1]) + 1)
				* sizeof(char))) == NULL)
      quit_error(serv);
    clt->nickname = strcpy(clt->nickname, clt->cmd[1]);
}

void		print_dlt(t_client *clt, t_serv *serv, t_chan *tmp)
{
  {
    dprintf(clt->fd, "Deleted channel: %s\n", tmp->name);
    dprintf(clt->fd, "Please choose a channel.\r\n");
    dlt_chan(serv->ch_head, clt->cmd[1], serv);
  }
}