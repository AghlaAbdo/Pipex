/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:35:51 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/22 16:36:42 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_word(char const **s, char c)
{
	if (**s == '\'' || **s == '"')
	{
		c = **s;
		(*s)++;
		while (**s && **s != c)
			(*s)++;
		(*s)++;
	}
	else
		while (**s && **s != c && **s != 9)
			(*s)++;
}

int	word_len(char const *str, char *c)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		*c = str[i];
		i++;
		while (str[i] && str[i] != *c)
			i++;
	}
	else
		while (str[i] && (str[i] != *c && str[i] != 9))
			i++;
	return (i);
}
