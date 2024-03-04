/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:11 by aaghla            #+#    #+#             */
/*   Updated: 2024/03/03 15:49:39 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../Libft/libft.h"

typedef struct s_data
{
	char	**paths;
	int		id_one;
	int		id_two;
}				t_data;

char	*find_path(char **env);
void	free_arr(char **arr);
char	*find_cmd_path(char **paths, char *cmd);
void	clear_exit(char **paths, char **cmd, int *fds, int status);

#endif