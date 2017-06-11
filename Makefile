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

DIR2    = src/server/

SRC2    = $(DIR2)main.c \
	$(DIR2)tools.c \
	$(DIR2)default.c \
	$(DIR2)cmd.c \
	$(DIR2)auth.c \
	$(DIR2)receive.c \
	$(DIR2)client_chain.c \
	$(DIR2)circu_buff.c \
	$(DIR2)chan.c \
	$(DIR2)cond.c \
	$(DIR2)propagation.c \
	$(DIR2)func_more.c \
	$(DIR2)more.c

OBJ2	= $(SRC2:.c=.o)

GCC	= gcc

RM	= rm -rf

CFLAGS	=  -Wall -W -Wextra

INC2    = -I ./includes/server/


$(SERVER): $(OBJ2)
	$(GCC) $(OBJ2) -o $(SERVER) $(CFLAGS) $(INC2)

all: $(SERVER)

.c.o:
	$(GCC) $(CFLAGS) $(INC2) -c $< -o $@

clean:
	$(RM) $(OBJ2)
	$(RM) *~
	$(RM) *#

fclean: clean
	$(RM) $(SERVER)

re: fclean all
