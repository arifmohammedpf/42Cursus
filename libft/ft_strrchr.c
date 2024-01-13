/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:46:40 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 09:49:35 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	while (i >= 0)
	{
		if (*s == (unsigned char) c)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}

// int main(void)
// {
//     const char *str = "Hello, World!";
//     int c = 'o';

//     char *result = ft_strrchr(str, c);
// 	printf("%s\n", result);
//     return 0;
// }
