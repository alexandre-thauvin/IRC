//
// Created by thauvi_a on 5/22/17.
//

#include "client.h"
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
  t_client 	*client;
  socklen_t 	s_in_size;
  fd_set	readfds;
  char 		*buff;
  char 		*tmp;

  client = malloc(sizeof(t_client));
  tmp = NULL;
  buff = malloc(512);
  while (1)
  {
    if (read(0, buff, 512) > 0)
    {
      buff = epur_buff(buff);
      fill_buff(buff, client, &tmp);
    }
  }
  return (0);
}
