/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:56 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/24 12:52:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_data *data, char **av, char **env)
{
	char	**cmd;
	char	*cmd_path;
	int		id;

	id = fork();
	if (id < 0)
		clear_exit(data, NULL, NULL);
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd)
			clear_exit(data, NULL, NULL);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds_first(av, data))
			clear_exit(data, cmd, cmd_path);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path);
	}
	data->cmd_i++;
	data->cmd_n--;
}

int	last_cmd(t_data *data, char **av, char **env, int j)
{
	char	**cmd;
	char	*cmd_path;
	int		id;

	id = fork();
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd)
			clear_exit(data, NULL, NULL);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds_last(av, data, j))
			clear_exit(data, cmd, cmd_path);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path);
		close_fds(data->fds, data->fds_n);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path);
	}
	close_fds(data->fds, data->fds_n);
	return (0);
}

void	exec_cmd(t_data *data, char **av, char **env, int j)
{
	char	**cmd;
	char	*cmd_path;
	int		id;

	id = fork();
	if (id < 0)
		clear_exit(data, NULL, NULL);
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd)
			clear_exit(data, NULL, NULL);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds(data, j))
			clear_exit(data, cmd, cmd_path);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path);
		close_fds(data->fds, data->fds_n);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path);
	}
}

int	fork_it(t_data *data, char **av, char **env, int cmd_n)
{
	int	j;

	init_pipes(data);
	first_cmd(data, av, env);
	j = 1;
	while (data->cmd_n)
	{
		if (data->cmd_n == 1)
			last_cmd(data, av, env, j);
		else
		{
			exec_cmd(data, av, env, j);
			data->cmd_i++;
			j++;
		}
		data->cmd_n--;
	}
	while (cmd_n)
	{
		wait(NULL);
		cmd_n--;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*path_v;

	path_v = find_path(env);
	if (!path_v)
		return (1);
	data.ac = ac;
	data.paths = ft_split(path_v, ':');
	if (!data.paths)
		return (2);
	data.cmd_n = cmd_count(&data, ac, av);
	data.fds_n = data.cmd_n -1;
	data.fds = init_fds(data.fds_n);
	if (!data.fds)
	{
		free_arr(data.paths);
		return (3);
	}
	fork_it(&data, av, env, data.cmd_n);
	free_arr(data.paths);
	return (0);
}
