/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:15:44 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/18 16:35:14 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	check(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("Correct usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	if (!envp)
		exit(1);
	if (!*av[2] || !*av[3])
		exit(1);
}

void	handle_files(char **av)
{
	int	infile;
	int	outfile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("Error opening the inpute file!", 2);
		exit(1);
	}
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("Error opening the output file!", 2);
		close(infile);
		exit(1);
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(infile);
	close(outfile);
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd1;
	char	*cmd2;

	check(ac, av, envp);
	handle_files(av);
	cmd1 = find_path(av[2], envp);
	if (!cmd1)
		exit(1);
	cmd2 = find_path(av[3], envp);
	if (!cmd2)
	{
		free(cmd1);
		exit(1);
	}
	handle_pipe(cmd1, cmd2, av, envp);
	if (cmd1)
		free(cmd1);
	if (cmd2)
		free(cmd2);
	return (0);
}
