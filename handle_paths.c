/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:24:00 by mgamraou          #+#    #+#             */
/*   Updated: 2025/02/16 15:34:52 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command(const char *full_cmd)
{
	char	**cmds;
	char	*cmd;

	cmds = ft_split(full_cmd, ' ');
	if (!cmds)
		return (NULL);
	cmd = ft_strdup(cmds[0]);
	clean_up(NULL, cmds);
	return (cmd);
}

char	*add_command(char *str, char *full_cmd)
{
	char	*cmd;
	char	*res;
	char	*result;

	cmd = get_command(full_cmd);
	res = ft_strjoin(str, "/");
	result = ft_strjoin(res, cmd);
	free(res);
	free(cmd);
	return (result);
}

char	*check_access(char **paths, char *str, char *cmd)
{
	int		i;
	char	*path;

	if (access(cmd, X_OK) == 0)
	{
		clean_up(str, paths);
		path = ft_strdup(cmd);
		return (path);
	}
	if (cmd[0] == '/' || cmd[0] == '.')
		perror("command not found!");
	i = 0;
	while (paths[i])
	{
		path = add_command(paths[i], cmd);
		if (path && access(path, X_OK) == 0)
		{
			clean_up(str, paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*str;
	char	*path;

	if (!cmd || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	str = ft_strdup(envp[i] + 5);
	if (!str)
		return (NULL);
	paths = ft_split(str, ':');
	if (!paths)
		return (free(str), NULL);
	path = check_access(paths, str, cmd);
	if (path)
		return (path);
	else
		clean_up(str, paths);
	return (NULL);
}
