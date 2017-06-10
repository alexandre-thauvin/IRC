/*
** cond.c.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 23:39:37 2017 Alexandre Thauvin
** Last update Fri Jun  9 23:39:38 2017 Alexandre Thauvin
*/

#include "server.h"

void		cond_join(t_client *clt, t_serv *serv)
{
  t_chan	*tmp;

  if (serv->ch_head)
  {
    tmp = find_chan(serv->ch_head, clt->cmd[1]);
    if (tmp == NULL)
    {
      clt->chan = add_chan(clt->cmd[1], serv);
      clt->chan->nb_users += 1;
    }
    else
    {
      clt->chan = tmp;
      tmp->nb_users += 1;
    }
    propag_join(serv, clt);
  }
  else
  {
    clt->chan = add_chan(clt->cmd[1], serv);
    dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, serv->ch_head->name);
  }
}

void		cond_print_at_all(t_client *clt, t_client *tmp)
{
  int i;

  i = 0;

  dprintf(tmp->fd, "[%s] %s", tmp->chan->name, clt->nickname);
  while (clt->cmd[i])
  {
    dprintf(tmp->fd, "%s", clt->cmd[i]);
    i++;
    if (clt->cmd[i] == NULL)
      dprintf(tmp->fd, "\r\n");
    else
      dprintf(tmp->fd, " ");
  }
}

void		cond_add_chan(t_serv *serv, t_chan *new, t_chan *current, char *name)
{
  new->next = NULL;
  if ((new->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
    quit_error(serv);
  new->name = strcpy(new->name, name);
  new->nb_users = 1;
  if (serv->ch_head->next == NULL)
    serv->ch_head->next = new;
  else
  {
    while (current->next != NULL)
      current = current->next;
    current->next = new;
  }
}

void		init_addToChain(t_client *new, int fd)
{
  new->nickname = "Anonymous-";
  new->front = 0;
  new->rear = 0;
  new->next = NULL;
  new->fd = fd;
  new->chan = NULL;
  new->nickname = "Anonymous ";
}
