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
  struct sockaddr_in	s_in_client;
  int 			fd;
  char 			*nickname;
  struct s_client	*next;
  char 			*buff_circu;
  int			front;
  int			rear;
  int			n;
}			t_client;

typedef struct 		s_serv
{
  int 			port;
  struct protoent	*pe;
  char 			**cmd;
  char 			**tab;
  t_client		*client;
}			t_serv;

void		choice(t_serv *);
void		default_buff(char *, char **);
void		fill_buff(char*, t_serv *, char **);
char 		**ma2d(int, int);
bool		check_end(char *);
unsigned int 	nb_word(char *);
char 		**cmd_to_tab(char*, char **, int);
void 		f_nick(t_serv *);
void 		f_list(t_serv *);
void 		f_join(t_serv *);
void 		f_part(t_serv *);
void		f_users(t_serv *);
void 		f_names(t_serv *);
void 		f_msg(t_serv *);
void 		f_send_file(t_serv *);
void 		f_accept_file(t_serv *);
t_client 	*addToChain(t_client *, int);
void		test_list(t_client *);
int 		max_fd(t_client*);
char		*cpy(t_serv *, char *);
void		buff_manage(t_serv *, char *);
char 		*epur_cmd(char *);

#endif //IRC_H
