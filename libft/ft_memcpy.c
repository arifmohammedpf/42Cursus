/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:53:22 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:05:21 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	if (!n)
		return (dst);
	if (!src && !dst)
		return (NULL);
	dst2 = dst;
	src2 = (unsigned char *)src;
	while (n != 0)
	{
		*dst2 = *src2;
		dst2++;
		src2++;
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	char s[] = "hello";
// 	char d[] = "sdasd";
// 	printf("og: %s \n", memcpy(d, s, 3));
// 	// printf("ft: %s", ft_memcpy(d, s, 3));
// }
