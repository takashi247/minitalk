NAME		:= libft.a

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

AR			:= ar

ARFLAGS		:= -rc

SRCS		:= ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c

SRCS_BONUS	:= ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

SRCS_PLUS	:= ft_strlen_u.c \
				ft_strdup_u.c \
				ft_strlcpy_u.c \
				ft_strlcat_u.c \
				ft_strjoin_u.c \
				ft_putstr_fd_u.c \
				ft_putendl_fd_u.c

OBJS		:= $(SRCS:.c=.o)

OBJS_BONUS	:= $(SRCS_BONUS:.c=.o)

OBJS_PLUS	:= $(SRCS_PLUS:.c=.o)

# DEBUG := -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS)

plus: $(OBJS) $(OBJS_BONUS) $(OBJS_PLUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_PLUS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_PLUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus plus