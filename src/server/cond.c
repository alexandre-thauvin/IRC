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

void		*print_chan(t_client *clt)
{
  unsigned int		i;

  i = 0;
  while (i < 11)
  {
    if (clt->chan[i])
    {
     printf("chan: %s // %d\n", clt->chan[i]->name, i);
    }
    i++;
  }
  return NULL;
}


t_chan		*check_chan(t_client *clt)
{
  unsigned int		i;

  i = 0;
  while (i < 10)
  {
    if (clt->chan[i])
    {
      if (strcmp(clt->cmd[1], clt->chan[i]->name) == 0)
	return clt->chan[i];
    }
    i++;
  }
  return NULL;
}

void		cond_join(t_client *clt, t_serv *serv)
{
  t_chan	*tmp;
  int 		i;

  if (serv->ch_head)
  {
    tmp = find_chan(serv->ch_head, clt->cmd[1]);
    if (tmp == NULL)
    {
      if ((i = find_empty(clt->chan)) == -1)
      {
	dprintf(clt->fd, "405 %s:Too Many channels\r\n", clt->cmd[1]);
	return ;
      }
      clt->chan[10] = add_chan(clt->cmd[1], serv);
      clt->chan[10]->nb_users += 1;
      clt->chan[i] = clt->chan[10];
      printf("[if]\n");
    }
    else
    {
      if ((check_chan(clt)))
      {
	dprintf(clt->fd, "714 Already in: %s\r\n", clt->cmd[1]);
	return ;
      }
      else
      {
	if ((i = find_empty(clt->chan)) == -1)
	{
	  dprintf(clt->fd, "405 %s:Too Many channels\r\n", clt->cmd[1]);
	  return ;
	}

	printf("[else]push at : %d\n", i);
	clt->chan[10] = tmp;
	if ((clt->chan[10]->nb_users += 1) > 50)
	{
	  dprintf(clt->fd, "471 %s:Too many people\r\n", clt->cmd[1]);
	  clt->chan[10] = NULL;
	  return ;
	}
	clt->chan[i] = clt->chan[10];
      }
    }
    propag_join(serv, clt);
  }
  else
  {
    clt->chan[10] = add_chan(clt->cmd[1], serv);
    clt->chan[find_empty(clt->chan)] = clt->chan[10];
    dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, serv->ch_head->name);
  }
}

void		cond_print_at_all(t_client *clt, t_client *tmp)
{
  int i;

  i = 0;

  dprintf(tmp->fd, "[%s] %s: ", tmp->chan[10]->name, clt->nickname);
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

void		init_addToChain(t_client *new, int fd, t_serv *serv)
{
  unsigned int 		i;

  i = 0;
  new->front = 0;
  new->rear = 0;
  new->next = NULL;
  new->fd = fd;
  if ((new->chan = malloc(11 * sizeof(t_client))) == NULL)
    quit_error(serv);
  while (i < 11)
  {
    new->chan[i] = NULL;
    i++;
  }
  new->user = false;
  new->nickname = "anonymous";
  new->registered = 0;
}
