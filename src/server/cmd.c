/*
** cmd.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:08:42 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:08:44 2017 Alexandre Thauvin
*/

#include "server.h"


void 	f_nick(t_client *clt, t_serv *serv)
{
  t_client *tmp;

  tmp = serv->head->next;
  if (strcmp(clt->cmd[1], "anonymous" ) == 0)
  {
    dprintf(clt->fd, "432 nickname invalid\r\n");
    return ;
  }
  while (tmp)
  {
    if (tmp->nickname && strcmp(clt->cmd[1], tmp->nickname) == 0)
    {
      dprintf(clt->fd, "433 This nickname is already use\r\n");
      return ;
    }
    tmp = tmp->next;
  }
  if (clt->cmd[1])
    print_nick(clt, serv);
  else
    dprintf(clt->fd, "\r\n");
}

void 	f_list(t_client *clt, t_serv *serv)
{
  if (serv->ch_head) {
    if (clt->cmd[1] == NULL)
      aff_chan(serv->ch_head, clt->fd);
  }
}

void 		f_join(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1])
  {
    if (clt->cmd[1][0] == '#')
      cond_join(clt, serv);
    else
      dprintf(clt->fd, "403 %s %s : Invalid channel name\r\n",
	      clt->nickname, clt->cmd[1]);
  }
  else
  dprintf(clt->fd, "421 Wrong Command\r\n");
}

void 	f_part(t_client *clt, t_serv *serv)
{
  t_chan	*tmp;

  if (clt->cmd[1])
  {
    if (serv->ch_head && clt->chan)
    {
      if ((tmp = check_chan(clt)))
      {
	propag_part(serv, clt);
	tmp->nb_users -= 1;
	clt->chan[find_it(clt, clt->cmd[1])] = NULL;
	clt->chan[10] = NULL;
	if (tmp->nb_users == 0)
	  print_dlt(clt, serv, tmp);
      }
      else
	dprintf(clt->fd, "Bad Chan\r\n");
    }
    else
      dprintf(clt->fd, "You are in any chan\r\n");
  }
  else
    dprintf(clt->fd, "Missing argument\r\n");
}

void 	f_users(t_client *clt, t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    dprintf(clt->fd, "%s", tmp->nickname);
    tmp = tmp->next;
    if (tmp)
      dprintf(clt->fd, "\n");
    else
      dprintf(clt->fd, "\r\n");
  }
  clt->nickname = clt->nickname;
}
