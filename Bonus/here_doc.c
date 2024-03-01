/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:07 by aaghla            #+#    #+#             */
/*   Updated: 2024/03/01 12:31:33 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_end(char *limitter, char *line, int flag)
{
	int	size;

	if (!line)
		return (1);
	size = ft_strlen(limitter);
	if (flag == FALSE)
	{
		if (!ft_strncmp(limitter, line, size) && (line[size] == '\n'))
			return (0);
	}
	else
	{
		if (!ft_strncmp(limitter, line, size) && (line[size] == '\n'
				|| line[size] == '\0'))
			return (0);
	}
	return (1);
}

static char	*read_rest(char **av, char *line, char *prev, char *input)
{
	while (check_end(av[2], line, FALSE))
	{
		if ((!line && ft_strchr(prev, '\n'))
			|| (line && line[0] == '\n' && !check_end(av[2], prev, TRUE)))
			break ;
		if (line && ft_strchr(line, '\n'))
			ft_putstr_fd("> ", 1);
		free(line);
		line = get_next_line(0);
		if (line && ft_strncmp(line, "\n", 1))
		{
			free(prev);
			prev = ft_strdup(line);
		}
		if (line && check_end(av[2], line, TRUE))
		{
			input = ft_strjoin(input, line);
			if (!input)
				return (free(line), free(prev), NULL);
		}
	}
	return (free(line), free(prev), input);
}

int	read_heredoc(t_data *data, char **av, char *line, char *input)
{
	char	*prev;

	if (pipe(data->here_fd) < 0)
		exit(1);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (line && check_end(av[2], line, FALSE))
	{
		prev = ft_strdup(line);
		if (!prev)
			return (free(line), 1);
		if (check_end(av[2], line, TRUE))
		{
			input = ft_strjoin(ft_strdup(""), line);
			if (!input)
				return (free(line), free(prev), free(input), 1);
		}
		input = read_rest(av, line, prev, input);
		if (!input)
			return (1);
		write(data->here_fd[1], input, ft_strlen(input));
	}
	else if (line)
		free(line);
	return (free(input), 0);
}
