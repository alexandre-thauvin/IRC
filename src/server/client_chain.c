//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

void 		addToChain(t_client *head, int fd)
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
}

void 		dltFromChain(t_client *head, int fd)
{
/*  int val;

  t_client *current =
  while (head->fd != fd)
    head = head->next;*/
  (void)fd;
  (void)head;
}