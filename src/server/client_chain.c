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
  (void)fd;
  new->fd = 10;
  new->nickname = "toto\n";
  if (head->next == NULL)
    head->next = new;
  else
  {
    while (current->next != NULL)
	current = current->next;
    current->next = new;
  }
  //printf("fd : %d\nnickname: %s\n", new->fd, new->nickname);
  return new;
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