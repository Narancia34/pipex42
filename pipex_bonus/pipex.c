/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:26:30 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/16 15:36:38 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_files(int ac, char **av)
{
	int	infile;
	int	outfile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		perror("error opening input file!");
		exit(1);
	}
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("error opening output file!");
		close(infile);
		exit (1);
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(infile);
	close(outfile);
}

int	main(int ac, char **av, char **envp)
{
	int	cmd_count;

	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdN outfile\n", 2);
		return (1);
	}
	handle_files(ac, av);
	cmd_count = ac - 3;
	handle_pipes(cmd_count, av, envp);
	return (0);
}
