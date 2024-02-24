/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:23:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/24 12:50:37 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	handle_fds(t_data *data, int j)
{
	if (dup2(data->fds[j -1][0], 0) < 0 || dup2(data->fds[j][1], 1) < 0)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	handle_fds_first(char **av, t_data *data)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		return (1);
	}
	if (dup2(fd, 0) < 0 || dup2(data->fds[0][1], 1) < 0)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	close_fds(data->fds, data->fds_n);
	return (0);
}

int	handle_fds_last(char **av, t_data *data, int j)
{
	int	fd;

	fd = open(av[data->ac -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[data->ac -1]);
		return (1);
	}
	if (dup2(data->fds[j -1][0], 0) < 0 || dup2(fd, 1) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	return (0);
}

int	cmd_count(t_data *data, int ac, char **av)
{
	int	count;

	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		data->cmd_i = 3;
		count = ac - 4;
	}
	else
	{
		data->cmd_i = 2;
		count = ac - 3;
	}
	return (count);
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