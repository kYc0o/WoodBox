##
## Makefile for makefile in /home/alexis/WoodBox/reception_xbee
## 
## Made by alexis
## Login   <alexis@epitech.net>
## 
## Started on  Wed May 13 14:50:37 2015 alexis
## Last update Wed May 13 14:50:37 2015 alexis
##

CC	= gcc

RM	= rm -f

CFLAGS	+= -I./include

NAME	= receptData

SRCS	= recept_data.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lmy -L.

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
