/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:13:11 by aaghla            #+#    #+#             */
/*   Updated: 2024/01/20 17:44:44 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	if ((!*needle && !*haystack) || (!len && !*needle))
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] && len--)
	{
		j = 0;
		n = len +1;
		while (needle[j] && needle[j] == haystack[i] && n)
		{
			i++;
			j++;
			n--;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i - j]);
		i -= j;
		i++;
	}
	return (NULL);
}
