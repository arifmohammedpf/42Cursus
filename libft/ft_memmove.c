/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:56:55 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:05:36 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dst2;
	char	*src2;

	dst2 = (char *)dst;
	src2 = (char *)src;
	if (!dst2 && !src2)
		return (dst2);
	if (dst2 == src2)
		return (dst2);
	if (dst2 < src2)
		return (ft_memcpy(dst2, src2, n));
	if (dst2 > src2)
		while (n--)
			dst2[n] = src2[n];
	return (dst2);
}

// int	main(void)
// {
// 	char dest[] = "asdasdasdasdasdasd";
// 	printf("og: %s \n", memmove(dest, "consectetur", 5));
// 	// printf("dup: %s\n", ft_memmove(dest, "consectetur", 5));
// }
