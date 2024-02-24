/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/24 11:38:01 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	leaks(void)
// {
// 	system("leaks pipex");
// }

int	handle_fds_one(char **av, int *fds, char **cmd)
{
	int	fd;

	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(fds[1]);
		perror(av[1]);
		free_arr(cmd);
		return (1);
	}
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[1]);
	close(fd);
	return (0);
}

int	exec_cmd_one(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;
	int		open;

	cmd = ft_split(av[2], ' ');
	if (!cmd || !*cmd)
		return (1);
	id = fork();
	if (id == -1)
		return (free_arr(cmd), perror("Error"), 1);
	if (id == 0)
	{
		open = handle_fds_one(av, fds, cmd);
		path_v = find_cmd_path(paths, cmd);
		if (!path_v || open)
			return (free_arr(cmd), free(path_v), 1);
		execve(path_v, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(path_v), 1);
	}
	return (free_arr(cmd), 0);
}

int	handle_fds_two(char **av, int *fds, char **cmd)
{
	int	fd;

	close(fds[1]);
	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fds[0]);
		perror(av[4]);
		free_arr(cmd);
		return (1);
	}
	dup2(fds[0], 0);
	dup2(fd, 1);
	close(fd);
	close(fds[0]);
	return (0);
}

int	exec_cmd_two(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;
	int		open;

	cmd = ft_split(av[3], ' ');
	if (!cmd || !*cmd)
		return (1);
	id = fork();
	if (id == -1)
		return (free_arr(cmd), 1);
	if (id == 0)
	{
		open = handle_fds_two(av, fds, cmd);
		path_v = find_cmd_path(paths, cmd);
		if (!path_v || open)
			return (free_arr(cmd), free(path_v), 1);
		execve(path_v, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(path_v), 1);
	}
	return (free_arr(cmd), 0);
}

	// atexit(leaks);
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
	if (exec_cmd_one(av, env, paths, fds))
		return (3);
	wait(NULL);
	close(fds[1]);
	if (exec_cmd_two(av, env, paths, fds))
		return (4);
	wait(&status);
	free_arr(paths);
	return (WEXITSTATUS(status));
}
