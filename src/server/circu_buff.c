/*
** circu_buff.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:08:19 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:08:21 2017 Alexandre Thauvin
*/

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
  int i;

  i = 0;
  if (clt->registered == 0 && strcmp(clt->nickname, "anonymous") != 0)
  {
    clt->registered = 1;
    dprintf(clt->fd, "001 Welcome\r\n");
  }
  while (clt->cmd[i])
  i++;
  if (i < 5)
    dprintf(clt->fd, "461 Not enough argument\r\n");
    else if (i > 5)
    dprintf(clt->fd, "461 Too much argument\r\n");
  else if (clt->user != false)
    dprintf(clt->fd, "462 You can't register you again\r\n");
  else if (clt->cmd[1])
  {
    /*if ((clt->user = malloc((strlen(clt->cmd[1]) + 1) * sizeof(char))) == NULL)
      quit_error(srv);*/
    //clt->user = strcpy(clt->user, clt->cmd[1]);
    clt->user = false;
  }
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
