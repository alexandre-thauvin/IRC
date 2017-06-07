//
// Created by thauvi_a on 5/22/17.
//

#ifndef PSU_2016_MYIRC_CLIENT_H
#define PSU_2016_MYIRC_CLIENT_H

#include <stdlib.h>

typedef struct 		s_client
{
  int 			fd;
  char			**cmd;
}			t_client;

char		*epur_buff(char *str);
int     	check_command(t_client *);
void		fill_buff(char *, t_client *, char **);
int		parse_command(int, t_client *);
void		command_list(t_client *client);
void 		command_users(t_client *client);
void 		command_names(t_client *client);
void 		command_msg(t_client *client);
void 		command_msgall(t_client *client);
void 		command_server(t_client *client);
void 		command_join(t_client *client);
void 		command_part(t_client *client);
void 		command_nick(t_client *client);
void 		command_accept(t_client *client);

#endif //PSU_2016_MYIRC_CLIENT_H
