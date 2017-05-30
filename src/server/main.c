/*
** main.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun May 22 15:16:49 2017 Alexandre Thauvin
** Last update Sun May 22 15:16:51 2017 Alexandre Thauvin
*/

#include <stdio.h>
#include "server.h"

char		**fill_tab(char **tab)
{
  tab[0] = "nick";
  tab[1] = "list";
  tab[2] = "join";
  tab[3] = "part";
  tab[4] = "names";
  tab[5] = "msg";
  tab[6] = "send_file";
  tab[7] = "accept_file";
  tab[8] = NULL;
  return (tab);
}

void 		handle_client(t_client *clt, t_serv *serv, t_client *head)
{
  char 		buf[512];
  char		*buf_tmp;

  buf_tmp = NULL;
  addToChain(head, clt->fd);
  serv->client = clt;
  serv->client->nickname = "";
  serv->tab = ma2d(9, 12);
  serv->tab = fill_tab(serv->tab);
  dprintf(clt->fd, "220 All rights\r\n");
  while (read(clt->fd, buf, 512) > 0)
    fill_buff(buf, serv, &buf_tmp);
}

int		clt_var(char **av, t_serv *serv)
{
  serv->port = atoi(av[1]);
  serv->pe = getprotobyname("TCP");
  if (!serv->pe)
    return (1);
  serv->s_in.sin_family = AF_INET;
  serv->s_in.sin_port = htons(serv->port);
  serv->s_in.sin_addr.s_addr = INADDR_ANY;
  serv->fd = socket(AF_INET, SOCK_STREAM, serv->pe->p_proto);
  if (serv->fd == -1)
    return (1);
  return (0);
}

int		main(int ac, char **av)
{
  t_client	clt;
  t_serv	serv;
  //pid_t 	fpid;
  t_client	*head;
  socklen_t 	s_in_size;


  head = (t_client *)malloc(sizeof(t_client));
  head->next = NULL;
  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  if (clt_var(av, &serv) == 1) {
    return (1);
  }
  s_in_size = sizeof(clt.s_in_client);
  if (bind(serv.fd, (const struct sockaddr *)&serv.s_in, sizeof(serv.s_in)) == -1)
    return (1);
  if (listen (serv.fd, 42 == -1) == -1)
    return (1);
  while (1)
  {
    clt.fd = accept(serv.fd, (struct sockaddr *)
     &clt.s_in_client, &s_in_size);
    if (clt.fd > 0)
      handle_client(&clt, &serv, head);
  }
  return 0;
  close(clt.fd);
}
