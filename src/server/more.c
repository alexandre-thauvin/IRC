/*
** more.c for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Sun Jun 11 15:12:08 2017 Alexandre Thauvin
** Last update Sun Jun 11 15:12:13 2017 Alexandre Thauvin
*/

#include "server.h"

int 	ret_u(t_client *tmp)
{
  int	u;

  u = 0;
  while (tmp->cmd[u] != NULL)
    u++;
  return (u);
}

