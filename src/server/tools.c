/*
** tools.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun May 22 15:16:58 2017 Alexandre Thauvin
** Last update Sun May 22 15:16:59 2017 Alexandre Thauvin
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp.h"

void		default_buff(t_cmd *cmd, char * buf)
{
  if (cmd->buf_tmp == NULL)
  {
    cmd->buf_tmp = (char *) malloc((strlen(buf) + 1) * sizeof(char));
    cmd->buf_tmp = strcpy(cmd->buf_tmp, buf);
  }
  else
    cmd->buf_tmp = strcat(cmd->buf_tmp, buf);
}

void		fill_buff(char *buf, t_cmd *cmd)
{
  if (check_end(buf))
  {
    if (cmd->buf_tmp == NULL)
    {
      cmd->nb_w = nb_word(buf);
      cmd->cmd = ma2d(cmd->nb_w + 1, 30);
      cmd->cmd = cmd_to_tab(buf, cmd->cmd, cmd->nb_w);
    }
    else
    {
      cmd->buf_tmp = strcat(cmd->buf_tmp, buf);
      cmd->nb_w = nb_word(cmd->buf_tmp);
      cmd->cmd = ma2d(cmd->nb_w + 1, 30);
      cmd->cmd = cmd_to_tab(cmd->buf_tmp, cmd->cmd, cmd->nb_w);
      cmd->buf_tmp = NULL;

    }
    choice(cmd);
  }
  else
    default_buff(cmd, buf);
}

unsigned int 	nb_word(char *line)
{
  unsigned int	w_count;
  char	*pos;

  w_count = 0;
  pos = line;
  while (*pos) {
    if (w_count == 0) {
      w_count = 1;
    }
    if (*pos == 32) {
      w_count++;
    }
    pos++;
  }
  return (w_count);
}

char 	**cmd_to_tab(char *str, char **tab, int nb_word)
{
  int	i;
  int	j;
  int	z;

  i = 0;
  z = 0;
  j = 0;
  if (str == NULL)
    return (0);
  while (i < nb_word)
  {
    while (str[z] != 32 && str[z] != '\0' && str[z] != '\n' && str[z] != '\r')
      tab[i][j++] = str[z++];
    tab[i][j] = '\0';
    j = 0;
    z++;
    i++;
  }
  tab[i] = 0;
  return (tab);
}

char 	**ma2d(int line, int col)
{
  int	i;
  char	**tab;

  i = 0;
  tab = (char **)malloc((line + 1) * sizeof(char *));
  while (i < line)
  {
    tab[i] = (char *)malloc(col * sizeof(char));
    i++;
  }
  tab[i] = NULL;
  return (tab);
}
