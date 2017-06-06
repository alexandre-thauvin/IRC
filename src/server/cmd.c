//
// Created by thauvi_a on 5/29/17.
//

#include "server.h"


void 	f_nick(t_client *clt)
{
  (void)clt;
}

void 	f_list(t_client *clt)
{
  (void)clt;
  dprintf(clt->fd, "JE SUIS F_LIST\r\n");
}
void 	f_join(t_client *clt)
{
  (void)clt;
}

void 	f_part(t_client *clt)
{
  (void)clt;
}

void 	f_users(t_client *clt)
{
  (void)clt;
}