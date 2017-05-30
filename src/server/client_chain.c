//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

void 		addToChain(t_client *head, int fd)
{
  t_client	*new = head;

  while (new->next != NULL)
    new = new->next;
  new = (t_client *)malloc(sizeof (t_client));
  new->fd = fd;
  new->next = NULL;
}

void 		dltFromChain(int fd)
{
  (void)fd;
}
