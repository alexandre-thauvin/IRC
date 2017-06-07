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
  tab[0] = "/nick";
  tab[1] = "/list";
  tab[2] = "/join";
  tab[3] = "/part";
  tab[4] = "/users";
  tab[5] = "/names";
  tab[6] = "/msg";
  tab[7] = "/send_file";
  tab[8] = "/accept_file";
  tab[9] = NULL;
  return (tab);
}

void 		handle_client(t_client *clt, t_serv *serv)
{
  char 		*buf;

  buf = (char *)malloc(512 * sizeof (char));
  serv->client = clt;
  serv->tab = ma2d(9, 12);
  serv->tab = fill_tab(serv->tab);
  clt->front = 0;
  clt->rear = -1;
  clt->buff_circu = (char *)malloc(1024 * sizeof(char));
  //dprintf(clt->fd, "220 All rights\r\n");
  if (read(clt->fd, buf, 512) > 0) {
    buf = epur_cmd(buf);
    buff_manage(clt, buf);
    fill_cmd(serv->head, clt->fd);
    choice(serv, clt->fd);
  }
}

t_client	*clt_var(char **av, t_serv *serv)
{
  t_client	*new;

  serv->port = atoi(av[1]);
  serv->pe = getprotobyname("TCP");
  if (!serv->pe)
    return (NULL);
  new = (t_client *)malloc(sizeof (t_client));
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->s_in_client.sin_family = AF_INET;
  new->s_in_client.sin_port = htons(serv->port);
  new->s_in_client.sin_addr.s_addr = INADDR_ANY;
  new->fd = socket(AF_INET, SOCK_STREAM, serv->pe->p_proto);
  new->next = NULL;
  new->nickname = (char *)malloc(30 * sizeof(char));
  new->nickname = "server";
  if (new->fd == -1)
    return (NULL);
  return (new);
}

void		check_select(t_client *head, fd_set *readfds, t_serv *serv)
{
  t_client	*tmp;
  int 		fd;
  socklen_t 	s_in_size;
  s_in_size = sizeof(head->s_in_client);


  tmp = head;
  if (FD_ISSET(head->fd, readfds))
  {
    printf("ADD CLIENT\n");
    fd = accept(head->fd, (struct sockaddr *)
     &tmp->s_in_client, &s_in_size);
    addToChain(head, fd);
  }
  tmp = tmp->next;
  while (tmp)
  {
    if (FD_ISSET(tmp->fd, readfds)) {
      handle_client(tmp, serv);
    }
    tmp = tmp->next;
  }
}

void		set_fd(fd_set *readfds, t_client *head)
{
  t_client *tmp;

  tmp = head;
  while (tmp)
  {
    FD_SET(tmp->fd, readfds);
    tmp = tmp->next;
  }
}

int		main(int ac, char **av)
{
  t_client	clt;
  t_serv	serv;
  fd_set	readfds;
  struct timeval tv;
  int 		ret_selec;

  serv.head = (t_client*) malloc(sizeof(t_client));
  clt.next = NULL;
  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  serv.head = clt_var(av, &serv);
  if (bind(serv.head->fd, (const struct sockaddr *)&serv.head->s_in_client, sizeof(serv.head->s_in_client)) == -1)
    return (1);
  if (listen (serv.head->fd, 42 == -1) == -1)
    return (1);
  while (1)
  {
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    set_fd(&readfds, serv.head);
    ret_selec = select(max_fd(serv.head) + 1, &readfds, NULL, NULL, &tv);
    if (ret_selec == -1)
     printf("Error Select\n");
    check_select(serv.head, &readfds, &serv);
    }
  return 0;
  close(clt.fd);
}
