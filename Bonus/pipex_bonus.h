/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:04:16 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/23 11:57:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct	s_data
{
	char	**paths;
	char	*path_v;
	char	*cmd_path;
	int		cmd_n;
	int		**fds;
}				t_data;

#endif