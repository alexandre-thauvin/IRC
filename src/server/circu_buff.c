//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

char		*cpy(t_client *clt, char *src)
{
  unsigned int 		i = 0;

  if (clt->rear != 0) {
    if (check_end(clt)) {
      memset(clt->buff_circu, '\0', 512);
      clt->rear = 0;
    }
  }
  while (src[i] != '\0')
  {
    clt->buff_circu[clt->rear] = src[i];
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

bool		buff_manage(t_client *clt, char *buff_tmp)
{
  clt->n = 512;
  clt->buff_circu = cpy(clt, buff_tmp);
  if (check_end(clt))
    return true;
  else
    return false;
}