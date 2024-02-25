/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:40:51 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/25 22:12:59 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

char	*find_cmd_path(char **arr, char **cmd)
{
	char	*cmd_p;
	int		i;

	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (!access(cmd[0], F_OK | X_OK))
			return (cmd[0]);
		else
		{
			perror(cmd[0]);
			return (NULL);
		}
	}
	i = 0;
	while (arr[i])
	{
		cmd_p = ft_strjoin(ft_strdup(arr[i]), "/");
		cmd_p = ft_strjoin(cmd_p, cmd[0]);
		if (!access(cmd_p, F_OK | X_OK))
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	perror(cmd[0]);
	return (NULL);
}

void	clear_exit(char **paths, char **cmd, char *path_v, int status)
{
	if (paths)
		free_arr(paths);
	if (cmd)
		free_arr(cmd);
	if (path_v)
		free(path_v);
	exit(status);
}
