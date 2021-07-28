NAME 		:= minitalk
NAME_SERVER := server
NAME_CLIENT := client

CC 			:= gcc

CFLAGS 		:= -Wall -Wextra -Werror

SRCS_SERVER	:= server.c

SRCS_CLIENT	:= client.c

OBJS_SERVER	:= $(SRCS_SERVER:.c=.o)

OBJS_CLIENT	:= $(SRCS_CLIENT:.c=.o)

INCLUDE		:= -I./libft/

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a

RM			:= rm -f

all:			$(NAME)

$(NAME):		$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER) $(LIBPATH)
				$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBPATH) -o $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJS_CLIENT) $(LIBPATH)
				$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBPATH) -o $(NAME_CLIENT)

.c.o:
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBPATH):
				$(MAKE) -C $(LIBDIR)

clean:
				$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
				$(MAKE) clean -C $(LIBDIR)

fclean:			clean
				$(RM) $(NAME_SERVER) $(NAME_CLIENT)
				$(MAKE) fclean -C $(LIBDIR)

re:				fclean all

.PHONY:			all clean fclean re