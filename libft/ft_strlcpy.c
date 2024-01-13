/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:19:16 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:18:23 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	slen;
	int	i;
	int	j;

	slen = ft_strlen(src);
	if (!dstsize)
		return (slen);
	i = 0;
	j = 0;
	while (src[i] && dstsize != 1)
	{
		dst[j] = src[i];
		i++;
		j++;
		dstsize--;
	}
	dst[j] = '\0';
	return (slen);
}

// int main(void)
// {
//     char dest[10];
//     const char *src = "Hello, World!";

//     size_t result = ft_strlcpy(dest, src, sizeof(dest));

//     printf("Copied string: %s\n", dest);

//     return 0;
// }