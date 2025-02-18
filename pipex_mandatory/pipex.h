/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:16:32 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/18 16:33:06 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"

char	*find_path(char *cmd, char **envp);
void	clean_up(char *str, char **arr);
char	*get_command(const char *full_cmd);
void	ft_error(int error);
char	*check_access(char **paths, char *str, char *cmd, char **envp);
void	ft_trow_error(int error);
void	handle_pipe(char *cmd1, char *cmd2, char **av, char **envp);
void	ft_error(int error);
void	execute_command(char *path, char **argv, char **envp);
void	handle_child1(char *cmd, char **av, char **envp, int *fd);
