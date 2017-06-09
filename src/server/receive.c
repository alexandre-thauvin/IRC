//
// Created by thauvi_a on 6/5/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

t_client	*find_clt(t_client *head, int fd, t_serv *serv)
{
  t_client	*tmp;

 if ((tmp = (t_client *)malloc(sizeof(t_client))) == NULL)
   quit_error(serv);
  tmp = head;
  while (tmp->fd != fd && tmp)
    tmp = tmp->next;
  return (tmp);
}

void		fill_cmd(t_client *head, int fd, t_serv *serv)
{
  char 			*cmd;
  t_client		*tmp;
  unsigned int 		i,z;

  tmp = find_clt(head, fd, serv);
  i = tmp->front;
  z = 0;
  if ((cmd = malloc((tmp->rear - tmp->front + 5) * sizeof(char))) == NULL)
    quit_error(serv);

  while (i <= tmp->rear)
  {
    cmd[z] = tmp->buff_circu[i];
    z++;
    i++;
  }
  cmd[z] = '\0';
  tmp->cmd = ma2d(nb_word(cmd) + 1, 512, serv);
  tmp->cmd = cmd_to_tab(cmd, tmp->cmd, nb_word(cmd));
}

