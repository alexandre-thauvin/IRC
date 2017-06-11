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
#include <sys/socket.h>
#include "server.h"

char		**fill_tab(char **tab)
{
  tab[0] = "NICK";
  tab[1] = "USER";
  tab[2] = "LIST";
  tab[3] = "JOIN";
  tab[4] = "PART";
  tab[5] = "USERS";
  tab[6] = "NAMES";
  tab[7] = "PRIVMSG";
  tab[8] = "SEND_FILE";
  tab[9] = "ACCEPT_FILE";
  tab[10] = "QUIT";
  tab[11] = "CAP";
  tab[12] = NULL;
  return (tab);
}
void 		handle_client(t_client *clt, t_serv *serv)
{
  char 		*buf;
  int 		ret = 0;

  if ((buf = malloc(512 * sizeof (char))) == NULL)
  {
    quit_error(serv);
    exit(1);
  }
  memset(buf, '\0', 512);
  serv->tab = ma2d(12, 12, serv);
  serv->tab = fill_tab(serv->tab);
  if ((ret = (int)read(clt->fd, buf, 512)) > 0 && ret < 511 && ret > 1)
  {
    printf("%s", buf);
    if (buff_manage(clt, buf))
    {
      fill_cmd(serv->head, clt->fd, serv);
      choice(serv, clt->fd);
    }
  }
  else if (read(clt->fd, buf, 512) <= 0)
  {
    dltFromChain(serv->head, clt->fd);
    close(clt->fd);
  }
  free(buf);
}

t_client	*clt_var(char **av, t_serv *serv)
{
  t_client	*new;

  serv->port = atoi(av[1]);
  serv->pe = getprotobyname("TCP");
  if (!serv->pe)
    return (NULL);
  new = malloc(sizeof (t_client));
  if (new == NULL)
    fprintf(stderr, "Unable to allocate memory for new node\n");
  new->s_in_client.sin_family = AF_INET;
  new->s_in_client.sin_port = htons(serv->port);
  new->s_in_client.sin_addr.s_addr = INADDR_ANY;
  new->fd = socket(AF_INET, SOCK_STREAM, serv->pe->p_proto);
  new->next = NULL;
  if ((new->nickname = malloc(30 * sizeof(char))) == NULL)
    quit_error(serv);
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
    fd = accept(head->fd, (struct sockaddr *)
     &tmp->s_in_client, &s_in_size);
    addToChain(head, fd, serv);
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

int			main(int ac, char **av)
{
  t_serv		serv;
  fd_set		readfds;
  struct timeval 	tv;
  int 			ret_selec;

  if ((serv.head = malloc(sizeof(t_client))) == NULL)
    quit_error(&serv);
  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    return (1);
  }
  serv.head = clt_var(av, &serv);
  serv.ch_head = NULL;
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
      quit_error(&serv);
    check_select(serv.head, &readfds, &serv);
    }
}
