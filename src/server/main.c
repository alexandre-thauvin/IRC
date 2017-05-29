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

void 		handle_client(t_client *clt, t_serv *serv)
{
  char 		buf[512];
  char		*buf_tmp;

  buf_tmp = NULL;
  serv->client = clt;
  serv->tab = ma2d(9, 12);
  serv->tab = fill_tab(serv->tab);
  dprintf(serv->client->fd, "220 All rights\r\n");
  while (read(clt->fd, buf, 512) > 0)
    fill_buff(buf, serv, &buf_tmp);
}

int		clt_var(t_client *clt, char **av, t_serv *serv)
{
  serv->port = atoi(av[1]);
  serv->pe = getprotobyname("TCP");
  if (!serv->pe)
    exit(1);
  serv->s_in.sin_family = AF_INET;
  serv->s_in.sin_port = htons(serv->port);
  serv->s_in.sin_addr.s_addr = INADDR_ANY;
  clt->fd = socket(AF_INET, SOCK_STREAM, serv->pe->p_proto);
  if (clt->fd == -1)
    return (1);
  return (0);
}

int		main(int ac, char **av)
{
  t_client	clt;
  t_serv	serv;
  //pid_t 	fpid;
  socklen_t 	s_in_size;

  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  if (clt_var(&clt, av, &serv) == 1)
    return (1);
  s_in_size = sizeof(clt.s_in_client);
  if (bind(clt.fd, (const struct sockaddr *)&serv.s_in, sizeof(serv.s_in)) == -1)
    return (1);
  if (listen (clt.fd, 42 == -1) == -1)
    return (1);
  while (1)
  {
    clt.fd = accept(clt.fd, (struct sockaddr *)
     &clt.s_in_client, &s_in_size);
    if (clt.fd > 0)
      handle_client(&clt, &serv);
  }
  close(clt.fd);
}
