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

/*
bool		isEmpty()
{

}

bool		isFull()
{
 //if HEAD = (tail%Size) + 1
}*/

char		*cpy(t_client *clt, char *src)
{
  unsigned int 		i = 0;

  //printf("REAR: %d\n", clt->rear);
  if ((clt->rear + 1) % clt->n != 0)
    clt->front = clt->rear + 1;
  else if (clt->rear + 1 == clt->n || ((clt->rear + 1) % clt->n == 0))
    clt->front = 0;
  while (src[i] != '\0' && src[i] != '\n')
  {
    if (((clt->rear) + 1) % clt->n == 0 && clt->rear != 0) {
      clt->rear = -1;
      //printf("reset\n");
    }
    //if (clt->rear + 1 != clt->front) {
      clt->buff_circu[clt->rear + 1] = src[i];
      //printf("copied : %c || at : %d\n", clt->buff_circu[clt->rear + 1], clt->rear + 1);
    clt->rear++;
    i++;
  }
  //clt->buff_circu[clt->rear + 1] = '\0';
  //clt->rear++;
  return clt->buff_circu;
}

void		buff_manage(t_client *clt, char *buff_tmp)
{
  clt->n = 512;
  clt->buff_circu = cpy(clt, buff_tmp);
  //printf("BUFF_CIRCU: |%s|\n", clt->buff_circu);
  //print_circu(clt->buff_circu);
  //printf("FRONT: %d | REAR: %d\n", clt->front, clt->rear);
  //dprintf(clt->fd, "BUFF: |%s|\n", clt->buff_circu);
}