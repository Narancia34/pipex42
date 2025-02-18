/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:03:15 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/14 14:42:52 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int error)
{
	if (error == 1)
		perror("pipe failed!");
	else if (error == 2)
		perror("fork failed!");
	exit(1);
}

void	execute_command(char *path, char **argv, char **envp)
{
	if (!path)
	{
		perror("command not found!");
		clean_up(path, argv);
		exit(127);
	}
	if (execve(path, argv, envp) == -1)
	{
		perror("execve failed!");
		exit(126);
	}
}

void	handle_child1(char *cmd, char **av, char **envp, int *fd)
{
	char	**argv;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	argv = ft_split(av[2], ' ');
	execute_command(cmd, argv, envp);
}

void	handle_child2(char *cmd, char **av, char **envp, int *fd)
{
	char	**argv;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	argv = ft_split(av[3], ' ');
	execute_command(cmd, argv, envp);
}

void	handle_pipe(char *cmd1, char *cmd2, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		ft_error(1);
	pid1 = fork();
	if (pid1 < 0)
		ft_error(2);
	if (pid1 == 0)
		handle_child1(cmd1, av, envp, fd);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			ft_error(2);
		if (pid2 == 0)
			handle_child2(cmd2, av, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, &status, 0);
		waitpid(pid2, &status, 0);
	}
}
