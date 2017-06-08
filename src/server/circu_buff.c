//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

char		*cpy(t_client *clt, char *src)
{
  unsigned int 		i = 0;

  if ((clt->rear + 1) % clt->n != 0)
    clt->front = clt->rear + 1;
  else if (clt->rear + 1 == clt->n || ((clt->rear + 1) % clt->n == 0))
    clt->front = 0;
  while (src[i] != '\0' && src[i] != '\n' && src[i] != '\r')
  {
    if (i >= 511)
    {
      printf("%d\nOVERFLOW\n", i);
      return NULL;
    }
    if (((clt->rear) + 1) % clt->n == 0 && clt->rear != 0) {
      clt->rear = -1;
    }
      clt->buff_circu[clt->rear + 1] = src[i];
    clt->rear++;
    i++;
  }
  return clt->buff_circu;
}

void		f_user(t_client *clt, t_serv *srv)
{
  if (clt->cmd[1])
  {
    if ((clt->user = malloc((strlen(clt->cmd[1]) + 1) * sizeof(char))) == NULL)
      quit_error(srv);
    printf("change user : %s\n", clt->cmd[1]);
    clt->user = strcpy(clt->user, clt->cmd[1]);
  }
  else
    dprintf(clt->fd, "Bad command\r\n");
  srv->head = srv->head;

}

void		buff_manage(t_client *clt, char *buff_tmp)
{
  clt->n = 513;
  clt->buff_circu = cpy(clt, buff_tmp);
}