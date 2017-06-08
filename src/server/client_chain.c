//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

t_client		*addToChain(t_client *head, int fd, t_serv *serv)
{
  t_client	*new;
  t_client	*current;
  printf("PING\n");
  if ((new = malloc(sizeof (t_client))) == NULL)
    quit_error(serv);
  current = head;
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->next = NULL;
  new->fd = fd;
  if ((new->nickname = malloc(512 * sizeof(char))) == NULL)
    quit_error(serv);
  new->nickname = "Anonymous-";
  new->chan = NULL;
  dprintf(fd, "001 Welcome\r\n");
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

void 		dltFromChain(t_client *head, int fd)
{
  t_client	*tmp;

  tmp = head;
  if (tmp->fd == fd)
  {
    if (tmp->next == NULL)
    {
      printf("There is only one node.\n");
      return;
    }
    head->fd = head->next->fd;
    head->next = head->next->next;
    return ;
  }
  while (tmp->next->fd != fd && tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
}