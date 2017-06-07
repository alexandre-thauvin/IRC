//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

void			addToBegin(t_client **head_ref, int fd)
{
  t_client	*new;

  new = (t_client *)malloc(sizeof(t_client));
  new->fd = fd;
  new->next = *head_ref;
  *head_ref = new;
}

t_client		*addToChain(t_client *head, int fd)
{
  t_client	*new;
  t_client	*current;

  printf("PING\n");
  new = (t_client *)malloc(sizeof (t_client));
  current = head;
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->next = NULL;
  new->fd = fd;
  new->nickname = (char *)malloc(30 * sizeof(char));
  new->nickname = "client";
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