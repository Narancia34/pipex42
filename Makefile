CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex

SRCS = ./pipex_mandatory/pipex.c ./pipex_mandatory/handle_paths.c ./pipex_mandatory/utils.c \
       ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strncmp.c ./libft/ft_strjoin.c ./libft/ft_strlen.c ./libft/ft_putstr_fd.c \
       ./libft/ft_substr.c ./libft/ft_memcpy.c
SRCS_BONUS = ./pipex_bonus/pipex.c ./pipex_bonus/handle_paths.c ./pipex_bonus/utils.c ./pipex_bonus/handle_pipes.c \
       ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strncmp.c ./libft/ft_strjoin.c ./libft/ft_strlen.c ./libft/ft_putstr_fd.c \
       ./libft/ft_substr.c ./libft/ft_memcpy.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
