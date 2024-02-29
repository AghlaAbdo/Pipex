/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/29 21:43:16 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_fds_one(char **av, int *fds)
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

void	exec_cmd_one(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;

	id = fork();
	if (id == -1)
		clear_exit(paths, NULL, fds, 1);
	if (id == 0)
	{
		cmd = ft_split(av[2], ' ');
		if (!cmd || !*cmd)
			clear_exit(paths, cmd, fds, 1);
		if (handle_fds_one(av, fds))
			clear_exit(paths, cmd, fds, 1);
		path_v = find_cmd_path(paths, cmd[0]);
		if (!path_v)
			clear_exit(paths, cmd, fds, 127);
		free_arr(paths);
		close(fds[0]);
		close(fds[1]);
		execve(path_v, cmd, env);
		perror("exec");
		free(path_v);
		clear_exit(NULL, cmd, NULL, 1);
	}
}

int	handle_fds_two(char **av, int *fds)
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

void	exec_cmd_two(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;

	id = fork();
	if (id == -1)
		clear_exit(paths, NULL, fds, 1);
	if (id == 0)
	{
		cmd = ft_split(av[3], ' ');
		if (!cmd || !*cmd)
			clear_exit(paths, cmd, fds, 1);
		if (handle_fds_two(av, fds))
			clear_exit(paths, cmd, fds, 1);
		path_v = find_cmd_path(paths, cmd[0]);
		if (!path_v)
			clear_exit(paths, cmd, fds, 127);
		free_arr(paths);
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
	char	*path_v;
	char	**paths;
	int		fds[2];
	int		status;

	if (ac != 5 || pipe(fds) == -1)
		return (1);
	path_v = find_path(env);
	if (!path_v)
		path_v = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin";
	paths = ft_split(path_v, ':');
	if (!paths)
		return (close(fds[0]), close(fds[1]), 1);
	exec_cmd_one(av, env, paths, fds);
	wait(NULL);
	exec_cmd_two(av, env, paths, fds);
	close(fds[1]);
	close(fds[0]);
	wait(&status);
	free_arr(paths);
	return (WEXITSTATUS(status));
}
