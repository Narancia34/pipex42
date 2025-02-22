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
		ft_putstr_fd("command not found!\n", 2);
		clean_up(path, argv);
		exit(127);
	}
	if (execve(path, argv, envp) == -1)
	{
		perror("execve failed!");
		clean_up(path, argv);
		exit(126);
	}
}

void	handle_child1(char **av, char **envp, int *fd)
{
	char	**argv;
	char	*cmd;
	int		input_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror("can't open inpute file");
		exit(1);
	}
	close(fd[0]);
	dup2(input_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(input_fd);
	argv = ft_split(av[2], ' ');
	cmd = find_cmd_path(av[2], envp);
	execute_command(cmd, argv, envp);
}

void	handle_child2(char **av, char **envp, int *fd)
{
	char	**argv;
	char	*cmd;

	cmd = find_cmd_path(av[3], envp);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	argv = ft_split(av[3], ' ');
	execute_command(cmd, argv, envp);
}

void	handle_pipe(char **av, char **envp)
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
		handle_child1(av, envp, fd);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			ft_error(2);
		if (pid2 == 0)
			handle_child2(av, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, &status, 0);
		waitpid(pid2, &status, 0);
	}
}
