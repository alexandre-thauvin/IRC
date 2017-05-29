//
// Created by thauvi_a on 5/22/17.
//

#ifndef IRC_H
#define IRC_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>

typedef struct 		s_client
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  socklen_t 		s_in_size;
  int 			fd;
  int 			port;
  int 			client_fd;
  int 			client2_fd;
  char 			*path;
  fd_set		readfds;
  int 			error;
}			t_client;

typedef struct 		s_data
{
  bool			isConnect;
  char 			*nickname;
  int 			id;
}			t_data;

typedef struct 		s_cmd
{
  unsigned int 		nb_w;
  char 			**cmd;
  char 			*buf_tmp;
  char 			**tab;
  t_data		*data;
  t_client		*client;
}			t_cmd;

void		choice(t_cmd *);
int		nb_line(char **tab);
void		default_buff(t_cmd *, char *);
void		fill_buff(char*, t_cmd *);
char 		**ma2d(int, int);
bool		check_end(char *);
unsigned int 	nb_word(char *);
char 		**cmd_to_tab(char*, char **, int);
void 		f_nick(t_cmd *);
void 		f_list(t_cmd *);
void 		f_join(t_cmd *);
void 		f_part(t_cmd *);
void		f_users(t_cmd *);
void 		f_names(t_cmd *);
void 		f_msg(t_cmd *);
void 		f_send_file(t_cmd *);
void 		f_accept_file(t_cmd *);

#endif //IRC_H
