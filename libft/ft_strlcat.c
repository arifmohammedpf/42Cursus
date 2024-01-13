/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:27:43 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:16:33 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		dlen;
	size_t		slen;

	j = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	i = dlen;
	if (dlen < (dstsize - 1) && dstsize > 0)
	{
		while (src[j] && (dlen + j) < (dstsize - 1))
		{
			dst[i] = src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	if (dlen >= dstsize)
		dlen = dstsize;
	return (dlen + slen);
}

// int main(void)
// {
//     char dest[20] = "Hello, ";
//     const char *src = "World!";

//     size_t result = ft_strlcat(dest, src, sizeof(dest));

//     printf("Concatenated string: %s\n", dest);

//     return 0;
// }