/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:32:20 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/29 21:52:12 by aaghla           ###   ########.fr       */
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

char	*find_cmd_path(char **paths, char *cmd)
{
	char	*cmd_p;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		else
			return (perror(cmd), NULL);
	}
	i = 0;
	while (paths[i])
	{
		cmd_p = ft_strjoin(ft_strdup(paths[i]), "/");
		if (!cmd_p)
			return (NULL);
		cmd_p = ft_strjoin(cmd_p, cmd);
		if (!cmd_p)
			return (NULL);
		if (!access(cmd_p, F_OK | X_OK))
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	return (perror(cmd), NULL);
}

void	clear_exit(t_data *data, char **cmd, char *path, int status)
{
	if (data)
	{
		close_fds(data);
		free_arr(data->paths);
	}
	if (cmd && !*cmd)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		free(cmd);
		if (path && !*path)
			status = 126;
		else
			status = 127;
	}
	else
	{
		if (cmd)
			free_arr(cmd);
		if (path)
			free(path);
	}
	exit(status);
}
