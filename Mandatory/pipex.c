/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/25 22:12:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	leaks(void)
// {
// 	system("leaks pipex");
// }

int	handle_fds_one(char **av, int *fds)
{
	int	fd;

	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(fds[1]);
		perror(av[1]);
		return (1);
	}
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[1]);
	close(fd);
	return (0);
}

void	exec_cmd_one(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;

	cmd = ft_split(av[2], ' ');
	if (!cmd || !*cmd)
		clear_exit(paths, cmd, NULL, 1);
	id = fork();
	if (id == -1)
		clear_exit(paths, cmd, NULL, 1);
	if (id == 0)
	{
		if (handle_fds_one(av, fds))
			clear_exit(paths, cmd, NULL, 1);
		path_v = find_cmd_path(paths, cmd);
		if (!path_v)
			clear_exit(paths, cmd, path_v, 127);
		execve(path_v, cmd, env);
		perror("exec");
		clear_exit(paths, cmd, path_v, 1);
	}
	free_arr(cmd);
}

int	handle_fds_two(char **av, int *fds)
{
	int	fd;

	close(fds[1]);
	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fds[0]);
		perror(av[4]);
		return (1);
	}
	dup2(fds[0], 0);
	dup2(fd, 1);
	close(fd);
	close(fds[0]);
	return (0);
}

void	exec_cmd_two(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;

	cmd = ft_split(av[3], ' ');
	if (!cmd || !*cmd)
		clear_exit(paths, cmd, NULL, 1);
	id = fork();
	if (id == -1)
		clear_exit(paths, cmd, NULL, 1);
	if (id == 0)
	{
		if (handle_fds_two(av, fds))
			clear_exit(paths, cmd, NULL, 1);
		path_v = find_cmd_path(paths, cmd);
		if (!path_v)
			clear_exit(paths, cmd, path_v, 127);
		execve(path_v, cmd, env);
		perror("exec");
		clear_exit(paths, cmd, path_v, 1);
	}
	free_arr(cmd);
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
		return (2);
	paths = ft_split(path_v, ':');
	exec_cmd_one(av, env, paths, fds);
	close(fds[1]);
	wait(NULL);
	exec_cmd_two(av, env, paths, fds);
	wait(&status);
	close(fds[0]);
	free_arr(paths);
	return (WEXITSTATUS(status));
}
