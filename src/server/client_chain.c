//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

t_client		*addToChain(t_client *head, int fd)
{
  t_client	*new;
  t_client	*current;

  new = (t_client *)malloc(sizeof (t_client));
  current = head;
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->next = NULL;
  new->fd = fd;
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
  while (tmp->next->fd != fd && tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
}