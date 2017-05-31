##
## Makefile for  in /home/thauvi_a/rendu/tek2/PSU_2016_malloc
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Jan 30 10:44:20 2017 Alexandre Thauvin
## Last update Tue May 30 14:42:45 2017 Alexandre Thauvin
##

SERVER	= server

CLIENT	= client

DIR1    = src/client/

DIR2    = src/server/

#RULE	= 2

SRC1    = $(DIR1)main.c

SRC2    = $(DIR2)main.c \
	$(DIR2)tools.c \
	$(DIR2)default.c \
	$(DIR2)cmd.c \
	$(DIR2)auth.c \
	$(DIR2)client_chain.c

OBJ1	= $(SRC1:.c=.o)

OBJ2	= $(SRC2:.c=.o)

GCC	= gcc

RM	= rm -rf

CFLAGS	=  -Wall -W -Wextra

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

re: fclean all
