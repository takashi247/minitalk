NAME 		:= minitalk
NAME_SERVER := server
NAME_CLIENT := client

CC 			:= gcc

CFLAGS 		:= -Wall -Wextra -Werror

SRCSDIR		:= ./srcs/

SRCS_SERVER	:= server.c
SRCS_SERVER	:= $(addprefix $(SRCSDIR), $(SRCS_SERVER))

SRCS_CLIENT	:= client.c
SRCS_CLIENT	:= $(addprefix $(SRCSDIR), $(SRCS_CLIENT))

OBJS_SERVER	:= $(SRCS_SERVER:.c=.o)

OBJS_CLIENT	:= $(SRCS_CLIENT:.c=.o)

INCLUDE		:= -I./libft/ -I./includes/

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a

DEBUG 		:=
# DEBUG		:= -g -fsanitize=address

RM			:= rm -f

all:			$(NAME)

$(NAME):		$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER) $(LIBPATH)
				$(CC) $(CFLAGS) $(DEBUG) $(OBJS_SERVER) $(LIBPATH) -o $(NAME_SERVER)

$(NAME_CLIENT):	$(OBJS_CLIENT) $(LIBPATH)
				$(CC) $(CFLAGS) $(DEBUG) $(OBJS_CLIENT) $(LIBPATH) -o $(NAME_CLIENT)

.c.o:
				$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

$(LIBPATH):
				$(MAKE) plus -C $(LIBDIR)

clean:
				$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
				$(MAKE) clean -C $(LIBDIR)

fclean:			clean
				$(RM) $(NAME_SERVER) $(NAME_CLIENT)
				$(MAKE) fclean -C $(LIBDIR)

re:				fclean all

bonus:			all

.PHONY:			all clean fclean re bonus