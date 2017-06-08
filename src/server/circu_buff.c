//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"

void		print_circu(char *str)
{
  printf("BUFF_CIRCU: |");
  for (int i = 0 ; i < 10 ; i++)
    printf("%c", str[i]);
  printf("|\n");

}

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
  //clt->buff_circu[clt->rear + 1] = '\0';
  //clt->rear++;
  return clt->buff_circu;
}

void		buff_manage(t_client *clt, char *buff_tmp)
{
  clt->n = 513;
  clt->buff_circu = cpy(clt, buff_tmp);
}