/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:26:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/16 16:11:33 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"

void	handle_pipes(int cmd_count, char **av, char **envp);
void	clean_up(char *str, char **arr);
char	*get_command(const char *full_cmd);
char	*add_command(char *str, char *full_cmd);
char	*check_access(char **paths, char *str, char *cmd, char **envp);
char	*find_path(char *cmd, char **envp);
void	ft_error(int error);
void	execute_command(char *path, char **argv, char **envp);
