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

char		*cpy(t_serv *serv, char *src)
{
  int 		i = 0;

  //printf("REAR: %d\n", serv->client->rear);
  if ((serv->client->rear + 1) % serv->client->n != 0)
    serv->client->front = serv->client->rear + 1;
  else if (serv->client->rear + 1 == serv->client->n || ((serv->client->rear + 1) % serv->client->n == 0))
    serv->client->front = 0;
  while (src[i] != '\0' && src[i] != '\n')
  {
    if (((serv->client->rear) + 1) % serv->client->n == 0 && serv->client->rear != 0) {
      serv->client->rear = -1;
      //printf("reset\n");
    }
    //if (serv->client->rear + 1 != serv->client->front) {
      serv->client->buff_circu[serv->client->rear + 1] = src[i];
      //printf("copied : %c || at : %d\n", serv->client->buff_circu[serv->client->rear + 1], serv->client->rear + 1);
    serv->client->rear++;
    i++;
  }
  //serv->client->buff_circu[serv->client->rear + 1] = '\0';
  //serv->client->rear++;
  return serv->client->buff_circu;
}

void		buff_manage(t_serv *serv, char *buff_tmp)
{
  serv->client->n = 512;
  serv->client->buff_circu = cpy(serv, buff_tmp);
  //printf("BUFF_CIRCU: |%s|\n", serv->client->buff_circu);
  //print_circu(serv->client->buff_circu);
  //printf("FRONT: %d | REAR: %d\n", serv->client->front, serv->client->rear);
  //dprintf(serv->client->fd, "BUFF: |%s|\n", serv->client->buff_circu);
}