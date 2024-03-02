/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:11 by aaghla            #+#    #+#             */
/*   Updated: 2024/03/02 10:47:43 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../Libft/libft.h"


char	*find_path(char **env);
void	free_arr(char **arr);
char	*find_cmd_path(char **paths, char *cmd);
void	clear_exit(char **paths, char **cmd, int *fds, int status);

#endif