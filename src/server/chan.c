/*
** chan.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:08:11 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:08:13 2017 Alexandre Thauvin
*/

#include "server.h"


t_chan		*set_chan(t_serv *serv)
{
  if ((serv->ch_head = malloc(sizeof(t_chan))) == NULL)
    quit_error(serv);
  return serv->ch_head;
}

void		aff_chan(t_chan *head, int fd)
{
  t_chan	*tmp;

  tmp = head;
  while (tmp)
  {
    dprintf(fd, "%s", tmp->name);
    tmp = tmp->next;
    if (tmp)
      dprintf(fd, "\n");
  }
  dprintf(fd, "\r\n");
}

t_chan		*find_chan(t_chan *head, char *name)
{
  t_chan	*tmp;

  tmp = head;
  while (tmp &&  strcmp(name, tmp->name) != 0)
    tmp = tmp->next;
  return (tmp);
}

t_chan		*add_chan(char *name, t_serv *serv)
{
  t_chan	*new;
  t_chan	*current;

  if (serv->ch_head == NULL)
  {
    serv->ch_head = set_chan(serv);
    serv->ch_head->next = NULL;
    serv->ch_head->nb_users = 1;
    if ((serv->ch_head->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
      quit_error(serv);
    serv->ch_head->name = strcpy(serv->ch_head->name, name);
    return serv->ch_head;
  }
  else
  {
    if ((new = malloc(sizeof (t_chan))) == NULL)
      quit_error(serv);
    if (new == NULL)
      fprintf(stderr, "Unable to allocate memory for new node\n");
    current = serv->ch_head;
    cond_add_chan(serv, new, current, name);
    return (new);
  }
}

void 		dlt_chan(t_chan *head, char *name, t_serv *serv)
{
  t_chan	*tmp;

  tmp = head;
  if (strcmp(name, tmp->name) == 0)
  {
    if (tmp->next == NULL)
    {
      serv->ch_head = NULL;
      return;
    }
    head->name = head->next->name;
    head->next = head->next->next;
    return ;
  }
  while (strcmp(name, tmp->next->name) != 0 && tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
}
