/*
** default.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun May 22 15:16:32 2017 Alexandre Thauvin
** Last update Sun May 22 15:16:35 2017 Alexandre Thauvin
*/


#include "server.h"

void	choice(t_serv *serv, int fd)
{
  void		(*func[9])(t_client *, t_serv *) = {f_nick, f_list, f_join, f_part,
				       f_users, f_names, f_msg, f_send_file, f_accept_file};
  void		(*funci)(t_client *, t_serv *);
  int	i;
  t_client		*tmp;
  int 			u = 0;

  i = 0;
  tmp = find_clt(serv->head, fd, serv);
  while (tmp->cmd[u] != NULL)
    u++;
  while (serv->tab[i] != NULL && strcmp(tmp->cmd[0], serv->tab[i]) != 0)
    i++;
  if (i <= 8)
  {
    funci = func[i];
    (*funci)(tmp, serv);
  }
  else
    print_at_all(tmp, serv);
}

bool 	check_end(char *line)
{
  int	i;

  i = 0;
  while (line)
  {
    if (line[i] == '\n')
      return (true);
    i++;
  }
  return (false);
}

int 	max_fd(t_client *client)
{
  t_client *tmp;
  int 	nb;

  nb = 0;
  tmp = client;
  while (tmp)
  {
    if (tmp->fd > nb)
      nb = tmp->fd;
    tmp = tmp->next;
  }
  return (nb);
}