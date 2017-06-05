/*
** parse_func.c for PSU_2016_myirc in /home/counil_m/project/PSU_2016_myirc/parse_func.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Mon Jun 05 14:40:23:23 ${YEAH} Maxime Counil
** Last update on Mon Jun 05 14:40:23:23 ${YEAH} Maxime Counil
*/

#înclude "client.h"


int     parse_command(int i, t_client *client)
{
  bool (*command[14])(t_client*);

  command[0] = &command_user;
  command[1] = &command_pass;
  command[2] = &command_cwd;
  command[3] = &command_cdup;
  command[4] = &command_quit;
  command[5] = &command_dele;
  command[6] = &command_pwd;
  command[7] = &command_pasv;
  command[8] = &command_port;
  command[9] = &command_help;
  command[10] = &command_noop;
  command[11] = &command_retr;
  command[12] = &command_stor;
  command[13] = &command_list;
  command[i](client);
  return (0);
}

int     check_command(t_client *client)
{
  int i = 0;
  char check[14][7] = {"SERVER", "NICK", "LIST", "JOIN", "PART",
		       "USERS", "NAMES", "$MESSAGES", "MSG",
   			"ACCEPT"};

  while (strncmp(check[i], client->save, strlen(check[i])) != 0 && i != 10)
    i++;
  if (i == 10)
  {
    if (client->user  == false && client->pass == false)
    {
      if (write(client->fd, "530 Please login "
       "with USER and PASS.\r\n", 38) == -1)
	return (0);
    }
    else
    {
      if (write(client->fd, "500 Synthax Error.\r\n", 20) == -1)
	return (0);
    }
  }
  else
  if (parse_command(i, client) == 1)
    return (1);
  return (0);
}

