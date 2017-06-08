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
#include "server.h"

void	quit_error(t_serv *serv)
{
  printf("quit_error\n");
  close_all(serv);
  exit(1);
}

void 		close_all(t_serv *serv)
{
  f_quit(serv->head, serv);
  return;
}

/*void		default_buff(char *buf, char **buf_tmp, t_serv *serv)
{
  if (*buf_tmp == NULL)
  {
    if ((*buf_tmp = malloc((strlen(buf) + 1) * sizeof(char))) == NULL)
    {
      close_all(serv);
      exit(1);
    }
    *buf_tmp = strcpy(*buf_tmp, buf);
  }
  else
    *buf_tmp = strcat(*buf_tmp, buf);
}


void		fill_buff(char *buf, t_serv *serv, char **buf_tmp)
{
  int		nb_w;

  if (check_end(buf))
  {
    if (*buf_tmp == NULL)
    {
      nb_w = nb_word(buf);
      serv->cmd = ma2d(nb_w + 1, 30);
      serv->cmd = cmd_to_tab(buf, serv->cmd, nb_w);
    }
    else
    {
      *buf_tmp = strcat(*buf_tmp, buf);
      nb_w = nb_word(*buf_tmp);
      serv->cmd = ma2d(nb_w + 1, 30);
      serv->cmd = cmd_to_tab(*buf_tmp, serv->cmd, nb_w);
      *buf_tmp = NULL;

    }
    choice(serv);
  }
  else
    default_buff(buf, buf_tmp, serv);
}*/

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

char 	**ma2d(int line, int col, t_serv *serv)
{
  int	i;
  char	**tab;

  i = 0;
  if ((tab = malloc((line + 1) * sizeof(char *))) == NULL)
  {
    quit_error(serv);
  }
  while (i < line)
  {
    if ((tab[i] = malloc(col * sizeof(char))) == NULL)
      quit_error(serv);
    i++;
  }
  tab[i] = NULL;
  return (tab);
}
