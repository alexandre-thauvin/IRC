##
## Makefile for  in /home/thauvi_a/rendu/tek2/PSU_2016_malloc
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Jan 30 10:44:20 2017 Alexandre Thauvin
## Last update Tue Jun  6 17:13:05 2017 counil_m
##

SERVER	= server

CLIENT	= client

DIR1    = src/client/

DIR2    = src/server/

#RULE	= 2

SRC1    = $(DIR1)main.c \
          $(DIR1)fill_buff.c \
	  $(DIR1)pars_func.c \
	  $(DIR1)msg_command.c \
	  $(DIR1)join_command.c

SRC2    = $(DIR2)main.c \
	$(DIR2)tools.c \
	$(DIR2)default.c \
	$(DIR2)cmd.c \
	$(DIR2)auth.c \
	$(DIR2)receive.c \
	$(DIR2)client_chain.c \
	$(DIR2)circu_buff.c \
	$(DIR2)chan.c

OBJ1	= $(SRC1:.c=.o)

OBJ2	= $(SRC2:.c=.o)

GCC	= gcc

RM	= rm -rf

CFLAGS	=  -Wall -W -Wextra -g

INC1    = -I ./includes/client/

INC2    = -I ./includes/server/


$(SERVER): $(OBJ2)
	$(GCC) $(OBJ2) -o $(SERVER) $(CFLAGS) $(INC2)

$(CLIENT): $(OBJ1)
	$(GCC) $(OBJ1) -o $(CLIENT) $(CFLAGS) $(INC1)

all: $(SERVER) $(CLIENT)

.c.o:
	$(GCC) $(CFLAGS) $(INC1) $(INC2) -c $< -o $@

clean:
	$(RM) $(OBJ1)
	$(RM) $(OBJ2)
	$(RM) *~
	$(RM) *#

fclean: clean
	$(RM) $(CLIENT)
	$(RM) $(SERVER)
	$(RM) vgcore*

re: fclean all
