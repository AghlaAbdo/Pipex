/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:40:51 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/23 08:58:18 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
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

	if (cmd[0][0] == '/')
	{
		if (!access(cmd[0], F_OK | X_OK))
			return (cmd[0]);
		else
			return (NULL);
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
