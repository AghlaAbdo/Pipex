/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:32:00 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/16 18:48:34 by aaghla           ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	int	id;
	char	*path_v;
	char	**path;
	int		i;
	int		fds[2];
	int		fd;

	i = 0;
	(void)ac;
	if (pipe(fds) == -1)
		return (1);
	path_v = find_path(env);
	path = ft_split(path_v, ':');
	id = fork();
	// atexit(leaks);
	if (id == 0)
	{
		sleep(1);
		close(fds[0]);
		fd = open(av[1], O_CREAT | O_RDWR, 0777);
		// printf("fd = %d\n", fd);
		dup2(fd, 0);
		dup2(fds[1], 1);
		close(fds[1]);
		close(fd);
		// printf("fd = %d\n", fd);
		while (path[i])
		{
			path_v = ft_strjoin(path[i], "/cat");
			if (!access(path_v, F_OK | X_OK))
			{
				// printf("path = %s\n", path_v);
				execve(path_v, (char *[]){path_v, NULL}, env);
			}
			free(path_v);
			i++;
		}
	}
	id = fork();
	i = 0;
	if (id == 0)
	{
		fd = open(av[2], O_CREAT | O_RDWR, 0777);
		close(fds[1]);
		dup2(fds[0], 0);
		dup2(fd, 1);
		close(fd);
		close(fds[0]);
		while (path[i])
		{
			path_v = ft_strjoin(path[i], "/wc");
			if (!access(path_v, F_OK | X_OK))
			{
				// printf("path = %s\n", path_v);
				execve(path_v, (char *[]){path_v, "-l", NULL}, env);
			}
			free(path_v);
			i++;
		}
	}
	free_arr(path);
	return (0);
}