//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"


void 	f_nick(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1] != NULL)
  {
    clt->nickname = malloc(strlen(clt->cmd[1] + 1) * sizeof(char));
    clt->nickname = strcpy(clt->nickname, clt->cmd[1]);
  }
  else
    dprintf(clt->fd, "Bad command\r\n");
  serv->head = serv->head;
}

void 	f_list(t_client *clt, t_serv *serv)
{
  (void)clt;
  dprintf(clt->fd, "clt->%s\r\n", clt->nickname);
  (void)serv;
}
void 	f_join(t_client *clt, t_serv *serv)
{
  (void)clt;
  (void)serv;
}

void 	f_part(t_client *clt, t_serv *serv)
{
  (void)clt;
  (void)serv;
}

void 	f_users(t_client *clt, t_serv *serv)
{
  t_client	*tmp;

  tmp = serv->head->next;
  printf("fd me :%s\n", clt->nickname);
  while (tmp)
  {
    dprintf(clt->fd, "|%s| |%d|\n", tmp->nickname, tmp->fd);
    tmp = tmp->next;
  }
  clt->nickname = clt->nickname;
}