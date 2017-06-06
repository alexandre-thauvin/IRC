//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"


void 	f_nick(t_client *clt, t_serv *serv)
{
  if (clt->cmd[1] != NULL)
  {
    clt->nickname = (char *)malloc(30 * sizeof(char));
    clt->nickname = strcpy(clt->nickname, clt->cmd[1]);
  }
  else
    dprintf(clt->fd, "Bad command\r\n");
  printf("|%s|\n", clt->nickname);
  serv->head = serv->head;
}

void 	f_list(t_client *clt, t_serv *serv)
{
  (void)clt;
  dprintf(clt->fd, "JE SUIS F_LIST\r\n");
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
    dprintf(tmp->fd, "|%s|\n", tmp->nickname);
    tmp = tmp->next;
  }
  clt->nickname = clt->nickname;
}