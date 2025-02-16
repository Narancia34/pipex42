CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex

SRCS = pipex.c handle_paths.c utils.c handle_pipes.c \
       ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strncmp.c ./libft/ft_strjoin.c ./libft/ft_strlen.c ./libft/ft_putstr_fd.c \
       ./libft/ft_substr.c ./libft/ft_memcpy.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
