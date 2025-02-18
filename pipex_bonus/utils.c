/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:09:49 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/16 16:10:13 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int error)
{
	if (error == 1)
		perror("pipe failed!");
	else if (error == 2)
		perror("fork failed!");
	else if (error == 3)
		perror("command not found!");
	exit(1);
}

void	clean_up(char *str, char **arr)
{
	int	i;

	if (str)
		free(str);
	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	execute_command(char *path, char **argv, char **envp)
{
	if (!path)
	{
		ft_putstr_fd("Command not found\n", 2);
		clean_up(path, argv);
		exit(127);
	}
	if (execve(path, argv, envp) == -1)
	{
		perror("execve");
		clean_up(path, argv);
		exit(126);
	}
}
