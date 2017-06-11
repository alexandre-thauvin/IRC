/*
** func_more.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun Jun 11 15:12:08 2017 Alexandre Thauvin
** Last update Sun Jun 11 15:12:13 2017 Alexandre Thauvin
*/

#include "server.h"

void 		handle_client(t_client *clt, t_serv *serv)
{
  char 		*buf;
  int 		ret = 0;

  if ((buf = malloc(512 * sizeof (char))) == NULL)
    quit_error(serv);
  memset(buf, '\0', 512);
  serv->tab = ma2d(12, 12, serv);
  serv->tab = fill_tab(serv->tab);
  if ((ret = (int)read(clt->fd, buf, 512)) > 0 && ret < 511 && ret > 1)
  {
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

void		check_arg(int ac)
{
  if (ac != 2)
  {
    printf("Usage: ./server port\n");
    exit (1);
  }
}

void	f_quit(t_client *clt, t_serv *serv)
{
  propag_quit(serv, clt);
  close (clt->fd);
  dltFromChain(serv->head, clt->fd);
}

t_chan		*check_chan(t_client *clt)
{
  unsigned int		i;

  i = 0;
  while (i < 10)
  {
    if (clt->chan[i] && clt->cmd[1] && clt->chan[i]->name)
    {
      if (strcmp(clt->cmd[1], clt->chan[i]->name) == 0)
	return (clt->chan[i]);
    }
    i++;
  }
  return (NULL);
}

void		print_join(t_client *clt, t_serv *serv)
{
  {
    clt->chan[10] = add_chan(clt->cmd[1], serv);
    clt->chan[find_empty(clt->chan)] = clt->chan[10];
    dprintf(clt->fd, ":%s JOIN : %s\r\n", clt->nickname, serv->ch_head->name);
  }
}