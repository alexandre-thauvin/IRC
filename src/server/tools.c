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
  t_client *tmp;

  tmp = serv->head->next;
  while (tmp)
  {
    close (tmp->fd);
    tmp = tmp->next;
  }
  close(serv->head->fd);
  exit(0);
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
