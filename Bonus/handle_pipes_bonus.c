/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:26:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/26 11:29:08 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**init_fds(int fds_n)
{
	int	**fds;
	int	i;

	fds = (int **)malloc(sizeof(int *) * fds_n);
	if (!fds)
		return (NULL);
	i = 0;
	while (i < fds_n)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!fds[i])
		{
			while (i >= 0)
			{
				free(fds[i--]);
			}
			free(fds);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

void	init_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->fds_n)
	{
		if (pipe(data->fds[i]) < 0)
		{
			while (--i >= 0)
			{
				close(data->fds[i][0]);
				close(data->fds[i][1]);
			}
			while (i < data->fds_n)
				free(data->fds[i++]);
			free(data->fds);
			free_arr(data->paths);
			if (data->here_doc)
			{
				close(data->here_fd[0]);
				close(data->here_fd[1]);
			}
			exit(1);
		}
	}
}

void	close_fds(int **fds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		free(fds[i++]);
	}
	free(fds);
}
