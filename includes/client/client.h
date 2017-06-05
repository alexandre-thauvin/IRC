//
// Created by thauvi_a on 5/22/17.
//

#ifndef PSU_2016_MYIRC_CLIENT_H
#define PSU_2016_MYIRC_CLIENT_H

#include <stdlib.h>

typedef struct 		s_client
{
  //int 			fd;
  char			**cmd;
}			t_client;

char		*epur_buff(char *str);
void		fill_buff(char *, t_client *, char **);
int		parse_command(int, t_client *);
#endif //PSU_2016_MYIRC_CLIENT_H
