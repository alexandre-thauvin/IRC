/*
** default.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:08:55 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:08:57 2017 Alexandre Thauvin
*/

#include "server.h"

void	choice(t_serv *serv, int fd)
{
  void		(*func[11])(t_client *, t_serv *) = {f_nick, f_user, f_list, f_join, f_part,
				       f_users, f_names, f_msg, f_send_file, f_accept_file, f_quit};
  void		(*funci)(t_client *, t_serv *);
  int		i;
  t_client	*tmp;
  int 		u = 0;
  static int 	check = 0;

  i = 0;
  tmp = find_clt(serv->head, fd, serv);
  while (tmp->cmd[u] != NULL)
    u++;
  while (serv->tab[i] != NULL && strcmp(tmp->cmd[0], serv->tab[i]) != 0)
    i++;
  printf("[default]cmd: %s\n", tmp->cmd[0]);
  if (i <= 10)
  {
    funci = func[i];
    (*funci)(tmp, serv);
  }
  else
  {
    if (check == 1)
      print_at_all(tmp, serv);
    check = 1;
  }
  if (tmp->registered == 0 && strcmp(tmp->nickname, "anonymous") != 0 && tmp->user != false)
  {
    dprintf(tmp->fd, "001 %s :Welcome\r\n", tmp->cmd[1]);
    tmp->registered = 1;
  }

}

bool 	check_end(t_client *clt)
{
  unsigned int	i;

  i = 0;
  while (clt->buff_circu && i < clt->rear)
  {
    if (clt->buff_circu[i] == '\r')
    {
      if (clt->buff_circu[i + 1] == '\n') {
	return (true);
      }
    }
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
