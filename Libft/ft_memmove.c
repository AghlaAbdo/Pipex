/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:19:03 by aaghla            #+#    #+#             */
/*   Updated: 2023/11/22 14:57:36 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*from;
	unsigned char		*to;
	size_t				n;

	from = (const unsigned char *)src;
	to = (unsigned char *)dst;
	n = len;
	if (from == to || len == 0)
		return (dst);
	if (from < to && to < from + len)
	{
		from += len - 1;
		to += len - 1;
		while (len-- > 0)
			*to-- = *from--;
	}
	else
	{
		while (n-- > 0)
			*to++ = *from++;
	}
	return (dst);
}
