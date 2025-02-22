/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:24:08 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/16 16:10:45 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_pipes_util_a(int prev_fd, int cmd_count, int i, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < cmd_count -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	handle_pipes_utils_b(int i, char **av, char **envp)
{
	char	**argv;
	char	*cmd_path;

	argv = ft_split(av[2 + i], ' ');
	cmd_path = find_cmd_path(argv[0], envp);
	execute_command(cmd_path, argv, envp);
}

void	handle_pipes_utils_c(int *prev_fd, int *fd)
{
	if ((*prev_fd) != -1)
		close(*prev_fd);
	close(fd[1]);
	(*prev_fd) = fd[0];
}

void	handle_input_file(char *file_name, int i)
{
	int	input;

	if (i == 0)
	{
		input = open(file_name, O_RDONLY);
		if (input == -1)
		{
			perror("can't open input file");
			exit(1);
		}
		dup2(input, STDIN_FILENO);
		close(input);
	}
}

void	handle_pipes(int cmd_count, char **av, char **envp)
{
	int		fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;

	i = -1;
	prev_fd = -1;
	while (++i < cmd_count)
	{
		if (pipe(fd) == -1)
			ft_error(1);
		pid = fork();
		if (pid < 0)
			ft_error(2);
		if (pid == 0)
		{
			handle_input_file(av[1], i);
			handle_pipes_util_a(prev_fd, cmd_count, i, fd);
			handle_pipes_utils_b(i, av, envp);
		}
		else
			handle_pipes_utils_c(&prev_fd, fd);
	}
	while (wait(NULL) > 0)
		;
}
