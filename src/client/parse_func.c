/*
** parse_func.c for PSU_2016_myirc in /home/counil_m/project/PSU_2016_myirc/parse_func.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Mon Jun 05 14:40:23:23 ${YEAH} Maxime Counil
** Last update on Mon Jun 05 14:40:23:23 ${YEAH} Maxime Counil
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

int     parse_command(int i, t_client *client)
{
  void (*command[14])(t_client*);

  command[0] = &command_server;
  command[1] = &command_nick;
  command[2] = &command_list;
  command[3] = &command_join;
  command[4] = &command_part;
  command[5] = &command_users;
  command[6] = &command_names;
  command[7] = &command_msgall;
  command[8] = &command_msg;
  command[9] = &command_accept;
  command[i](client);
  return (0);
}

int     check_command(t_client *client)
{
  int i = 0;
  char check[10][10] = {"/server", "/nick", "/list", "/join", "/part",
		       "/users", "/names", "/$messages", "/msg",
   			"/accept"};

  while (strncmp(check[i], client->cmd[0], strlen(check[i])) != 0 && i != 10)
    i++;
  if (i == 10)
     printf("Bad Command\n");
  else
  {
    if (parse_command(i, client) == 1)
      return (1);
  }
  return (0);
}

