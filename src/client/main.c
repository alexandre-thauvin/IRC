//
// Created by thauvi_a on 5/22/17.
//

#include "client.h"
#include <unistd.h>

int	main()
{
  t_client 	*client;
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
      check_command(client);
    }
  }
  return (0);
}
