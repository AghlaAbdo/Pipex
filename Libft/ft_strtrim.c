/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:47:47 by aaghla            #+#    #+#             */
/*   Updated: 2023/11/21 14:33:26 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isthere(char const *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static int	skipstart(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (isthere(set, s[i]))
			i++;
		else
			break ;
	}
	if (!s[i])
		return (-1);
	return (i);
}

static int	skipend(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (isthere(set, s[i]))
			i--;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		n;

	n = 0;
	if (!s1 || !set)
		return (NULL);
	i = skipstart(s1, set);
	if (i < 0)
		return (ft_strdup(""));
	j = skipend(s1, set);
	str = (char *)malloc((j - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (i <= j)
		str[n++] = s1[i++];
	str[n] = '\0';
	return (str);
}
