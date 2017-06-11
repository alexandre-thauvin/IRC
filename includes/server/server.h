/*
** server.h for  in /home/thauvi_a/rendu/psu/PSU_2016_myirc/src/server
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Fri Jun  9 22:10:14 2017 Alexandre Thauvin
** Last update Fri Jun  9 22:10:15 2017 Alexandre Thauvin
*/

#ifndef IRC_H
# define IRC_H

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string.h>
# include <arpa/inet.h>
# include <stdbool.h>


typedef struct		s_chan
{
  char 			*name;
  unsigned int		nb_users;
  struct s_chan		*next;
}			t_chan;

typedef struct		s_ch_chan
{
  struct s_chan		*chan;
  struct s_chan		*next;
}			t_ch_chan;

typedef struct 		s_client
{
  struct sockaddr_in	s_in_client;
  int 			fd;
  bool 			user;
  char 			*nickname;
  struct s_client	*next;
  char 			*buff_circu;
  unsigned int		front;
  unsigned int		rear;
  unsigned int		n;
  char 			**cmd;
  t_chan		**chan;
  int 			registered;
}			t_client;

typedef struct 		s_serv
{
  struct s_client	*head;
  int 			port;
  struct protoent	*pe;
  char 			**tab;
  t_chan		*ch_head;
}			t_serv;

void		choice(t_serv *, int);
char 		**ma2d(int, int, t_serv *);
bool		check_end(t_client *);
unsigned int 	nb_word(char *);
char 		**cmd_to_tab(char*, char **, int);
void 		f_nick(t_client *, t_serv *);
void 		f_list(t_client *, t_serv *);
void 		f_join(t_client *, t_serv *);
void 		f_part(t_client *, t_serv *);
void		f_users(t_client *, t_serv *);
void 		f_names(t_client *, t_serv *);
void 		f_msg(t_client *, t_serv *);
void 		f_send_file(t_client *, t_serv *);
void 		f_accept_file(t_client *, t_serv *);
void 		f_user(t_client *, t_serv *);
void 		f_quit(t_client *, t_serv *);
t_client 	*addToChain(t_client *, int, t_serv *);
int 		max_fd(t_client*);
char		*cpy(t_client *, char *);
bool		buff_manage(t_client *, char *);
void 		fill_cmd(t_client *, int, t_serv *);
t_client	*find_clt(t_client *, int, t_serv *);
void		print_at_all(t_client *, t_serv *);
t_chan		*add_chan(char *, t_serv *);
t_chan		*find_chan(t_chan *, char *);
void		aff_chan(t_chan *, int);
void 		dlt_chan(t_chan *, char *, t_serv *);
void		quit_error(t_serv *);
void 		dltFromChain(t_client *, int);
t_chan		*set_chan(t_serv *);
void 		propag_join(t_serv *, t_client *);
void 		propag_part(t_serv *, t_client *);
void		cond_join(t_client *, t_serv *);
void		cond_print_at_all(t_client *, t_client *);
void		cond_add_chan(t_serv *, t_chan *, t_chan *, char *);
void		init_addToChain(t_client *, int, t_serv *);
t_chan		*check_chan(t_client *);
int		find_empty(t_chan **);
void		*print_chan(t_client *);
int 		find_it(t_client *clt, char *);

#endif //IRC_H
