//
// Created by thauvi_a on 6/8/17.
//

#include "server.h"



void		aff_chan(t_chan *head, int fd)
{
  t_chan	*tmp;

  tmp = head;
  while (tmp)
  {
    dprintf(fd, "%s\r\n", tmp->name);
    tmp = tmp->next;
  }
}

t_chan		*set_chan(t_chan *head, t_serv *serv)
{
  if ((head = malloc(sizeof(t_chan))) == NULL)
    quit_error(serv);
  head->next = NULL;
  head->nb_users = 0;
  if ((head->name = malloc((strlen("General Chan") + 1) * sizeof(char))) == NULL)
    quit_error(serv);
  head->name = strcpy(head->name, "General Chan");
  return head;
}

t_chan		*find_chan(t_chan *head, char *name)
{
  t_chan	*tmp;

  tmp = head;
  while (tmp &&  strcmp(name, tmp->name) != 0)
    tmp = tmp->next;
  return tmp;
}

t_chan		*add_chan(t_chan *head, char *name, t_serv *serv)
{
  t_chan	*new;
  t_chan	*current;

  printf("PING\n");
  if ((new = malloc(sizeof (t_chan))) == NULL)
  {
    close_all(serv);
    exit(1);
  }
  current = head;
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->next = NULL;
  if ((new->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
    quit_error(serv);
  new->name = strcpy(new->name, name);
  new->nb_users = 0;
  if (head->next == NULL)
    head->next = new;
  else
  {
    while (current->next != NULL)
      current = current->next;
    current->next = new;
  }
  return new;
}

void 		dlt_chan(t_chan *head, char *name)
{
  t_chan	*tmp;

  tmp = head;
  if (strcmp(name, tmp->name) == 0)
  {
    if (tmp->next == NULL)
    {
      printf("There is only one node.\n");
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