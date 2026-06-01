/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:40:18 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/26 18:09:31 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	to_copy;

	srclen = ft_strlen(src);
	if (dstsize == 0)
	{
		return (srclen);
	}
	to_copy = srclen;
	if (dstsize - 1 < srclen)
	{
		to_copy = dstsize - 1;
	}
	ft_memcpy(dst, src, to_copy);
	dst[to_copy] = '\0';
	return (srclen);
}
