/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/03/05 19:03:36 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_fds_one(char **av, int *fds)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		return (1);
	}
	if (dup2(fd, 0) < 0 || dup2(fds[1], 1) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	exec_cmd_one(t_data *data, char **av, char **env, int *fds)
{
	char	*path_v;
	char	**cmd;

	data->id_one = fork();
	if (data->id_one == -1)
		clear_exit(data->paths, NULL, fds, 1);
	if (data->id_one == 0)
	{
		cmd = ft_split(av[2], ' ');
		if (!cmd || !*cmd)
			clear_exit(data->paths, cmd, fds, 1);
		if (handle_fds_one(av, fds))
			clear_exit(data->paths, cmd, fds, 1);
		path_v = find_cmd_path(data->paths, cmd[0]);
		if (!path_v)
			clear_exit(data->paths, cmd, fds, 127);
		free_arr(data->paths);
		close(fds[0]);
		close(fds[1]);
		execve(path_v, cmd, env);
		perror("exec");
		free(path_v);
		clear_exit(NULL, cmd, NULL, 1);
	}
}

static int	handle_fds_two(char **av, int *fds)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[4]);
		return (1);
	}
	if (dup2(fds[0], 0) < 0 || dup2(fd, 1) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	exec_cmd_two(t_data *data, char **av, char **env, int *fds)
{
	char	*path_v;
	char	**cmd;

	data->id_two = fork();
	if (data->id_two == -1)
		clear_exit(data->paths, NULL, fds, 1);
	if (data->id_two == 0)
	{
		cmd = ft_split(av[3], ' ');
		if (!cmd || !*cmd)
			clear_exit(data->paths, cmd, fds, 1);
		if (handle_fds_two(av, fds))
			clear_exit(data->paths, cmd, fds, 1);
		path_v = find_cmd_path(data->paths, cmd[0]);
		if (!path_v)
			clear_exit(data->paths, cmd, fds, 127);
		free_arr(data->paths);
		close(fds[0]);
		close(fds[1]);
		execve(path_v, cmd, env);
		perror("exec");
		free(path_v);
		clear_exit(NULL, cmd, NULL, 1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*path_v;
	int		fds[2];
	int		status;

	if (ac != 5 || pipe(fds) == -1)
		return (1);
	path_v = find_path(env);
	if (!path_v)
		return (close(fds[0]), close(fds[1]), 1);
	data.paths = ft_split(path_v, ':');
	if (!data.paths)
		return (close(fds[0]), close(fds[1]), 1);
	exec_cmd_one(&data, av, env, fds);
	exec_cmd_two(&data, av, env, fds);
	close(fds[1]);
	close(fds[0]);
	waitpid(data.id_one, NULL, 0);
	waitpid(data.id_two, &status, 0);
	free_arr(data.paths);
	return (WEXITSTATUS(status));
}
