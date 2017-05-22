/*
** default.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun May 22 15:16:32 2017 Alexandre Thauvin
** Last update Sun May 22 15:16:35 2017 Alexandre Thauvin
*/

#include "ftp.h"

int	nb_line(char **tab)
{
  int i;

  i = 0;
  while (tab[i] != NULL)
    i++;
  return (i);
}

void	choice(t_cmd *cmd)
{
  void		(*func[8])(t_cmd *) = {f_nick, f_list, f_join, f_part,
				       f_users, f_names, f_msg, f_send_file, f_accept_file};
  void		(*funci)(t_cmd *);
  int	i;

  i = 0;
  while (cmd->tab[i] != NULL && strcmp(cmd->cmd[0], cmd->tab[i]) != 0)
    i++;
  if (i >= 7)
  {
    funci = func[i];
    (*funci)(cmd);
  }
  else
    dprintf(cmd->client->client_fd, "500 Unknown command.\r\n");
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
