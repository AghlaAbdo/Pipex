/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:57:40 by aaghla            #+#    #+#             */
/*   Updated: 2023/11/20 09:06:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size > len_dst)
		len = len_src + len_dst;
	else
		len = len_src + size;
	while (src[i] && (len_dst + 1) < size)
		dst[len_dst++] = src[i++];
	dst[len_dst] = '\0';
	return (len);
}
