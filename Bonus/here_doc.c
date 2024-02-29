/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:45:07 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/29 22:45:24 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_end(char *limitter, char *line)
{
	int	size;

	if (!line)
		return (1);
	size = ft_strlen(limitter);
	if (!ft_strncmp(limitter, line, size) && (line[size] == '\n'
			|| line[size] == '\0'))
		return (0);
	return (1);
}

static void	read_rest(t_data *data, char **av, char *line, char *input)
{
	char	*prev;
	
	prev = ft_strdup(line);
	printf("before\n");
	while ((check_end(av[2], line) && line) || (!line && ft_strchr(prev, '\n')))
	{
		printf("after\n");
		line = get_next_line(0);
		if (line && check_end(av[2], line))
		{
			ft_putstr_fd("> ", 1);
			free(line);
			prev = ft_strdup(line);
			input = ft_strjoin(input, line);
			if (!input)
			{
				free(line);
				exit(1);
			}
		}
	}
	free(line);
	write(data->here_fd[1], input, ft_strlen(input));
	free(input);
}

void	read_heredoc(t_data *data, char **av)
{
	char	*line;
	char	*input;

	if (pipe(data->here_fd) < 0)
		exit(1);
	input = ft_strdup("");
	if (!input)
		exit(1);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (line)
	{
		input = ft_strjoin(input, line);
		if (!input)
			exit(1);
	}
	read_rest(data, av, line, input);
}
