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
	cmd_path = find_path(argv[0], envp);
	if (!cmd_path)
	{
		clean_up(cmd_path, argv);
		exit(1);
	}
	execute_command(cmd_path, argv, envp);
}

void	handle_pipes_utils_c(int *prev_fd, int *fd, int status, int pid)
{
	if ((*prev_fd) != -1)
		close(*prev_fd);
	close(fd[1]);
	(*prev_fd) = fd[0];
	waitpid(pid, &status, 0);
}

void	handle_pipes(int cmd_count, char **av, char **envp)
{
	int		fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	prev_fd = -1;
	while (i < cmd_count)
	{
		if (pipe(fd) == -1)
			ft_error(1);
		pid = fork();
		if (pid < 0)
			ft_error(2);
		if (pid == 0)
		{
			handle_pipes_util_a(prev_fd, cmd_count, i, fd);
			handle_pipes_utils_b(i, av, envp);
		}
		else
			handle_pipes_utils_c(&prev_fd, fd, status, pid);
		i++;
	}
}
