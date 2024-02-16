/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:59:34 by aaghla            #+#    #+#             */
/*   Updated: 2023/11/22 15:13:21 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*locate;
	size_t			res;

	res = count * size;
	if (res < count && res)
		return (NULL);
	locate = malloc(res);
	if (!locate)
		return (NULL);
	ft_bzero(locate, count * size);
	return (locate);
}
