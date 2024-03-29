/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:04:16 by aaghla            #+#    #+#             */
/*   Updated: 2024/03/02 11:01:20 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0
# define CHECK_LOOP 0
# define CHECK_JOIN 1

typedef struct s_data
{
	char	**paths;
	int		ac;
	int		cmd_n;
	int		cmd_i;
	int		**fds;
	int		here_fd[2];
	int		here_doc;
	int		fds_n;
}				t_data;

int		**init_fds(int fds_n);
void	init_pipes(t_data *data);
void	close_fds(t_data *data);
int		handle_fds(t_data *data, int j);
int		handle_fds_first(char **av, t_data *data);
int		handle_fds_last(char **av, t_data *data, int j);
int		cmd_count(t_data *data, int ac, char **av);
void	free_arr(char **arr);
char	*find_path(char **env);
char	*find_cmd_path(char **paths, char *cmd);
void	clear_exit(t_data *data, char **cmd, char *path, int status);
int		read_heredoc(t_data *data, char **av, char *line, char *input);

#endif