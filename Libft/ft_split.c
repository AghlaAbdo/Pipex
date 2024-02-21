/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:46:45 by aaghla            #+#    #+#             */
/*   Updated: 2024/02/21 21:47:43 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static int	wordcount(char const *s, char c)
{
	int		i;
	int		count;
	char	first_c;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == 9))
			i++;
		if (s[i] == '\'' || s[i] == '"')
		{
			first_c = s[i++];
			while (s[i] && s[i] != first_c)
				i++;
		}
		if (s[i])
			count++;
		while (s[i] && (s[i] != c || s[i] != 9))
			i++;
	}
	return (count);
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
		while (str[i] && (str[i] != *c || str[i] != 9))
			i++;
	return (i);
}

static char	*word(char const *str, char c)
{
	char	*word;
	int		i;
	int		j;

	i = word_len(str, &c);
	word = malloc((i +1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	if (c == '\'' || c == '"')
		i++;
	while (str[i] && str[i] != c)
		word[j++] = str[i++];
	word[i] = '\0';
	return (word);
}

static char	**freearr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

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
		while (**s && **s != c)
			(*s)++;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c || *s == 9))
			s++;
		if (*s)
		{
			arr[i] = word(s, c);
			if (!arr[i])
				return (freearr(arr, i));
			i++;
		}
		skip_word(&s, c);
	}
	arr[i] = NULL;
	return (arr);
}
