/*
** join_command.c for PSU_2016_myirc in /home/counil_m/project/PSU_2016_myirc/join_command.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Mon Jun 05 15:23:12:12 ${YEAH} Maxime Counil
** Last update on Mon Jun 05 15:23:12:12 ${YEAH} Maxime Counil
*/

#include "client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <stdio.h>
#include <stdint.h>

void 	command_server(t_client *client)
{
  struct sockaddr_in s_in;
  struct protoent *pe;
  socklen_t s_in_size;

  s_in.sin_family = AF_INET;
  if (client->cmd[2] == NULL)
    s_in.sin_port = htons(6697);
  else
    s_in.sin_port = htons((atoi(client->cmd[2]));
  s_in.sin_addr.s_addr = inet_addr(client->cmd[1]);
  s_in_size = sizeof(s_in);
  pe = getprotobyname("TCP");
  if (!pe)
    return;
  client->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (client->fd == -1)
    return;
  if (connect(client->fd, (struct sockaddr *) &s_in, s_in_size) == -1)
    return;
}

void 	command_join(t_client *client)
{
  (void)client;
}

void 	command_part(t_client *client)
{
  (void)client;
}

void 	command_nick(t_client *client)
{
  printf("LOL : %s\n", client->cmd[1]);
  
}

void 	command_accept(t_client *client)
{
  (void)client;
}