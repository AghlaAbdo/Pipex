/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/20 10:59:27 by aaghla           ###   ########.fr       */
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

void	leaks(void)
{
	system("leaks pipex");
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
	// free_arr(arr);
	// free_arr(cmd);
	// exit(1);
	return (NULL);
}

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
		open = handle_fds_one(av, fds);
		path_v = find_cmd_path(paths, cmd);
		// fprintf(stderr, "%s\n", path_v);
		if (!path_v || open)
			return (free_arr(cmd), free(path_v), 1);
		execve(path_v, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(path_v), 1);
	}
	// printf("herein\n");
	// wait(NULL);
	// waitpid(id, NULL, 0);
	return (free_arr(cmd), 0);
}

int	handle_fds_two(char **av, int *fds)
{
	int	fd;

	close(fds[1]);
	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
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

int	exec_cmd_two(char **av, char **env, char **paths, int *fds)
{
	char	*path_v;
	char	**cmd;
	int		id;
	int		open;

	(void)env;
	cmd = ft_split(av[3], ' ');
	if (!cmd || !*cmd)
		return (1);
	id = fork();
	if (id == -1)
		return (free_arr(cmd), 1);
	// printf("id = %d\n", id);
	if (id == 0)
	{
		open = handle_fds_two(av, fds);
		path_v = find_cmd_path(paths, cmd);
		if (!path_v || open)
			return (free_arr(cmd), free(path_v), 1);
		// fprintf(stderr, "%s\n", path_v);
		execve(path_v, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(path_v), 1);
	}
	// waitpid(id, NULL, 0);
	return (free_arr(cmd), 0);
}

int	main(int ac, char **av, char **env)
{
	char	*path_v;
	char	**paths;
	int		fds[2];
	int		status;
	// int		rtrn;

	// atexit(leaks);
	if (ac != 5 || pipe(fds) == -1)
		return (1);
	path_v = find_path(env);
	paths = ft_split(path_v, ':');
	if (exec_cmd_one(av, env, paths, fds))
		return (2);
	wait(NULL);
	close(fds[1]);
	if (exec_cmd_two(av, env, paths, fds))
		return (3);
	wait(&status);
	free_arr(paths);
	return (WEXITSTATUS(status));
}
