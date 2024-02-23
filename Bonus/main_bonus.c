/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:56 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/23 22:02:08 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	cmd_count(int ac, char **av)
{
	int	count;

	if (!ft_strncmp(av[1], "here_doc", 9))
		count = ac - 4;
	else
		count = ac - 3;
	// printf("count = %d\n", count);
	return (count);
}

char	*find_cmd_path(char **arr, char *cmd)
{
	char	*cmd_p;
	int		i;

	if (cmd[0] == '/')
	{
		if (!access(cmd, F_OK | X_OK))
			return (cmd);
		else
			return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		cmd_p = ft_strjoin(ft_strdup(arr[i]), "/");
		cmd_p = ft_strjoin(cmd_p, cmd);
		if (!access(cmd_p, F_OK | X_OK))
			return (cmd_p);
		free(cmd_p);
		i++;
	}
	// printf("error: %s\n", cmd);
	perror(cmd);
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

void	close_fds(int **fds, int n)
{
	int	i;

	i = 0;
	// int pid = getpid();
	// printf("pid = %d\n", pid);
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

int	handle_fds_first(char **av, t_data *data)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		// fprintf(stderr, "open failed\n");
		close(data->fds[0][1]);
		perror(av[1]);
		return (1);
	}
	// close(data->fds[0][0]);
	dup2(fd, 0);
	dup2(data->fds[0][1], 1);
	// close(data->fds[0][1]);
	close(fd);
	close_fds(data->fds, data->cmd_n -1);
	return (0);
}

int	first_cmd(t_data *data, char **av, char **env)
{
	char	**cmd;
	int		id;

	id = fork();
	if (id == 0)
	{
		cmd = ft_split(av[2], ' ');
		data->cmd_path = find_cmd_path(data->paths, cmd[0]);
		handle_fds_first(av, data);
		if (!data->cmd_path)
			return (free_arr(cmd), free(data->cmd_path), 1);
		execve(data->cmd_path, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(data->cmd_path), 1);
	}
	return (0);
}

int	**init_fds(int cmd_n)
{
	int	**fds;
	int	i;

	fds = (int **)malloc(sizeof(int *) * cmd_n -1);
	// if (!fds)
		// do something
	i = 0;
	while (i < cmd_n -1)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (fds);
}

int	handle_fds_last(char **av, t_data *data, int j)
{
	int	fd;

	fd = open(av[data->cmd_n -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(data->fds[j][0]);
		perror(av[data->cmd_n -1]);
		// free_arr(cmd);
		return (1);
	}
	dup2(data->fds[j -1][0], 0);
	// dup2(fd, 1);
	close(fd);
	return (0);
}

int	last_cmd(t_data *data, char **av, char **env, int j, int i, int temp)
{
	char	**cmd;
	int		id;

	id = fork();
	if (id == 0)
	{
		cmd = ft_split(av[i], ' ');
		data->cmd_path = find_cmd_path(data->paths, cmd[0]);
		handle_fds_last(av, data, j);
		if (!data->cmd_path)
			return (free_arr(cmd), free(data->cmd_path), 1);
		close_fds(data->fds, temp);
		execve(data->cmd_path, cmd, env);
		perror("exec");
		return (free_arr(cmd), free(data->cmd_path), 1);
	}
	close_fds(data->fds, temp);
	wait(NULL); 
	return (0);
}

int	handle_fds(char **av, t_data *data, int j)
{
	(void)av;
	dup2(data->fds[j -1][0], 0);
	dup2(data->fds[j][1], 1);
	// close(data->fds[j -1][0]);
	// close(data->fds[j][0]);
	// close(data->fds[j][1]);
	// close(data->fds[j -1][1]);
	return (0); 
}


int	fork_it(t_data *data, char **av, char **env)
{
	char	**cmd;
	int		id;
	int		i;
	int		j;
	int		temp;

	for (int i = 0; i < data->cmd_n -1; i++)
		pipe(data->fds[i]);
	if (first_cmd(data, av, env))
		exit(1);
	i = 3;
	j = 1;
	// printf("cmd_n = %d\n", data->cmd_n);
	temp = data->cmd_n -1;
	data->cmd_n--;
	while (data->cmd_n > 1)
	{
		// printf("forked\n");
		id = fork();
		if (id == 0)
		{
			cmd = ft_split(av[i], ' ');
			data->cmd_path = find_cmd_path(data->paths, cmd[0]);
			handle_fds(av, data, j);
			if (!data->cmd_path)
				return (free_arr(cmd), free(data->cmd_path), 1);
			close_fds(data->fds, temp);
			execve(data->cmd_path, cmd, env);
			perror("exec");
			return (free_arr(cmd), free(data->cmd_path), 1);
		}
		// printf("[0] = %d\n", data->fds[j -1][0]);
		// printf("[1] = %d\n", data->fds[j -1][1]);
		// close(data->fds[j -1][0]);
		// close(data->fds[j -1][1]);
		i++;
		j++;
		wait(NULL);
		data->cmd_n--;
		if (data->cmd_n  == 1)
		{
			// printf("last av = %s\n", av[i]);
			last_cmd(data, av, env, j, i, temp);
		}
	}
		// close_fds(data->fds, temp);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.path_v = find_path(env);
	if (!data.path_v)
		return (1);
	data.paths = ft_split(data.path_v, ':');
	data.cmd_n = cmd_count(ac, av);
	data.fds = init_fds(data.cmd_n);
	fork_it(&data, av, env);
	// sleep(7);
	return (0);
}
