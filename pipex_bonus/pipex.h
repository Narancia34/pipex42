/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:26:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/18 17:12:40 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	handle_pipes(int cmd_count, char **av, char **envp);
void	clean_up(char *str, char **arr);
void	ft_error(int error);
char	*find_cmd_path(char *full_cmd, char **envp);
void	execute_command(char *path, char **argv, char **envp);

#endif
