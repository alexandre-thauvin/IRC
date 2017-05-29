##
## Makefile for  in /home/thauvi_a/rendu/tek2/PSU_2016_malloc
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Jan 30 10:44:20 2017 Alexandre Thauvin
## Last update Mon May 29 11:08:57 2017 Alexandre Thauvin
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
	$(DIR2)auth.c

OBJ1	= $(SRC1:.c=.o)

OBJ2	= $(SRC2:.c=.o)

GCC	= gcc

RM	= rm -rf

CFLAGS	=  -Wall -Werror -W -Wextra

INC1    = -I ./includes/client/

INC2    = -I ./includes/server/


$(CLIENT): $(OBJ1)
	$(GCC) $(OBJ1) -o $(CLIENT) $(CFLAGS) $(INC1)


$(SERVER): $(OBJ2)
	$(GCC) $(OBJ2) -o $(SERVER) $(CFLAGS) $(INC2)

all: $(CLIENT) $(SERVER)

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
