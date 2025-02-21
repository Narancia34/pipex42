/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:16:32 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/18 17:13:11 by mgamraou         ###   ########.fr       */
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

void	clean_up(char *str, char **arr);
void	handle_pipe(char **av, char **envp);
void	ft_error(int error);
void	execute_command(char *path, char **argv, char **envp);
char	*find_cmd_path(char *full_cmd, char **envp);

#endif
