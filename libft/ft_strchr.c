/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:45:50 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 09:47:04 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = (unsigned char)c;
	while (*s)
	{
		if (*s == c2)
			return ((char *)s);
		s++;
	}
	if (c2 == '\0')
		return ((char *)s);
	return (NULL);
}

// int main(void)
// {
//     const char *str = "Hello, World!";
//     int c = 'o';

//     char *result = ft_strchr(str, c);
// 	printf("%s\n", result);
//     return 0;
// }