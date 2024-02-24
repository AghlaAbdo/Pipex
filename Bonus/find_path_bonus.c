/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:32:20 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/24 12:46:13 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*find_cmd_path(char **arr, char *cmd)
{
	char	*cmd_p;
	int		i;

	if (cmd[0] == '/')
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		else
		{
			perror(cmd);
			return (NULL);
		}
	}
	i = 0;
	while (arr[i])
	{
		cmd_p = ft_strjoin(ft_strdup(arr[i]), "/");
		cmd_p = ft_strjoin(cmd_p, cmd);
		if (!access(cmd_p, F_OK | X_OK))
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	perror(cmd);
	return (NULL);
}

void	clear_exit(t_data *data, char **cmd, char *path)
{
	free_arr(data->paths);
	close_fds(data->fds, data->fds_n);
	if (cmd)
		free_arr(cmd);
	if (path)
		free(path);
	exit(5);
}
