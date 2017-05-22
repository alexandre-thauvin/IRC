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
#include "ftp.h"

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

void 		handle_client(t_client *init)
{
  char 		buf[512];
  t_data	dat;
  t_cmd		cmd;

  cmd.client = init;
  dat.isConnect = false;
  cmd.data = &dat;
  cmd.buf_tmp = NULL;
  cmd.tab = ma2d(9, 12);
  cmd.tab = fill_tab(cmd.tab);
  dprintf(cmd.client->client_fd, "220 All rights\r\n");
  while (read(init->client_fd, buf, 512) > 0)
    fill_buff(buf, &cmd);
}

void		init_var(t_client *init, char **av)
{
  init->s_in_size = sizeof(init->s_in_client);
  init->port = atoi(av[1]);
  init->pe = getprotobyname("TCP");
  if (!init->pe)
    exit(1);
  init->s_in.sin_family = AF_INET;
  init->s_in.sin_port = htons(init->port);
  init->s_in.sin_addr.s_addr = INADDR_ANY;
  init->path = (char *)malloc((strlen(av[2]) + 1) * sizeof(char));
  init->path = strcpy(init->path, av[2]);
  if (chdir(init->path) != 0)
  {
    printf("bad path\n");
    exit(1);
  }
  init->fd = socket(AF_INET, SOCK_STREAM, init->pe->p_proto);
  if (init->fd == -1)
    exit(1);
}

int		main(int ac, char **av)
{
  t_client	init;
  pid_t 	fpid;

  if (ac != 3)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  init_var(&init, av);
  bind(init.fd, (const struct sockaddr *)&init.s_in, sizeof(init.s_in));
  listen (init.fd, 42 == -1);
  while (1)
  {
    init.client_fd = accept(init.fd, (struct sockaddr *)
     &init.s_in_client, &init.s_in_size);
  }
  close(init.fd);
}
