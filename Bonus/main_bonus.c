/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:56 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/26 14:57:00 by aaghla           ###   ########.fr       */
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
		clear_exit(data, NULL, NULL, 1);
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd || !*cmd)
			clear_exit(data, cmd, av[data->cmd_i], 1);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds_first(av, data))
			clear_exit(data, cmd, cmd_path, 1);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path, 127);
		free_arr(data->paths);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path, 1);
	}
	data->cmd_i++;
	data->cmd_n--;
}

int	last_cmd(t_data *data, char **av, char **env, int j)
{
	char	**cmd;
	char	*cmd_path;
	int		id;
	int		status;

	id = fork();
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd || !*cmd)
			clear_exit(data, cmd, av[data->cmd_i], 1);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds_last(av, data, j))
			clear_exit(data, cmd, cmd_path, 1);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path, 127);
		close_fds(data->fds, data->fds_n);
		free_arr(data->paths);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path, 1);
	}
	close_fds(data->fds, data->fds_n);
	waitpid(id, &status, 0);
	return (WEXITSTATUS(status));
}

void	exec_cmd(t_data *data, char **av, char **env, int j)
{
	char	**cmd;
	char	*cmd_path;
	int		id;

	id = fork();
	if (id < 0)
		clear_exit(data, NULL, NULL, 1);
	if (id == 0)
	{
		cmd = ft_split(av[data->cmd_i], ' ');
		if (!cmd || !*cmd)
			clear_exit(data, cmd, av[data->cmd_i], 1);
		cmd_path = find_cmd_path(data->paths, cmd[0]);
		if (handle_fds(data, j))
			clear_exit(data, cmd, cmd_path, 1);
		if (!cmd_path)
			clear_exit(data, cmd, cmd_path, 127);
		close_fds(data->fds, data->fds_n);
		free_arr(data->paths);
		execve(cmd_path, cmd, env);
		perror("exec");
		clear_exit(data, cmd, cmd_path, 1);
	}
}

int	fork_it(t_data *data, char **av, char **env, int cmd_n)
{
	int	j;
	int status;

	init_pipes(data);
	first_cmd(data, av, env);
	if (data->here_doc)
	{
		close(data->here_fd[0]);
		close(data->here_fd[1]);
	}
	j = 1;
	while (data->cmd_n > 1)
	{
		exec_cmd(data, av, env, j);
		data->cmd_i++;
		j++;
		data->cmd_n--;
	}
	status = last_cmd(data, av, env, j);
	while (cmd_n -1)
	{
		wait(NULL);
		cmd_n--;
	}
	return (status);
}

void	leaks(void)
{
	system("leaks pipex_bonus");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*path_v;
	int		rtrn;

	// atexit(leaks);
	path_v = find_path(env);
	if (!path_v)
		return (1);
	data.ac = ac;
	data.cmd_n = cmd_count(&data, ac, av);
	data.paths = ft_split(path_v, ':');
	if (!data.paths)
		return (2);
	data.fds_n = data.cmd_n -1;
	data.fds = init_fds(data.fds_n);
	if (!data.fds)
	{
		free_arr(data.paths);
		return (3);
	}
	rtrn = fork_it(&data, av, env, data.cmd_n);
	free_arr(data.paths);
	// sleep(10);
	return (rtrn);
}
