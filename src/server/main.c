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
  char 		*buf;

  buf = (char *)malloc(512 * sizeof (char));
  printf("BOOM\n");
  serv->client = clt;
  serv->client->nickname = "";
  serv->tab = ma2d(9, 12);
  serv->tab = fill_tab(serv->tab);
  serv->client->front = 0;
  serv->client->rear = -1;
  serv->client->buff_circu = (char *)malloc(1024 * sizeof(char));
  dprintf(clt->fd, "220 All rights\r\n");
  if (read(clt->fd, buf, 512) > 0) {
    buf = epur_cmd(buf);
    buff_manage(serv, buf);
    write(clt->fd, buf, strlen(buf));
    write(clt->fd, "\r\n", 2);
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
    if (FD_ISSET(tmp->fd, readfds))
      handle_client(tmp, serv);
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
  t_client 	*head;
  t_serv	serv;
  fd_set	readfds;
  struct timeval tv;
  int 		ret_selec;

  head = (t_client*) malloc(sizeof(t_client));
  clt.next = NULL;
  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  head = clt_var(av, &serv);
  if (bind(head->fd, (const struct sockaddr *)&head->s_in_client, sizeof(head->s_in_client)) == -1)
    return (1);
  if (listen (head->fd, 42 == -1) == -1)
    return (1);
  while (1)
  {
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    set_fd(&readfds, head);
    ret_selec = select(max_fd(head) + 1, &readfds, NULL, NULL, &tv);
    /*if (ret_selec == -1 || ret_selec == 0)
     printf("Error Select\n");*/
    check_select(head, &readfds, &serv);
    }
  return 0;
  close(clt.fd);
}
