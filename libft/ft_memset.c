/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:52 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:05:48 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = b;
	while (len != 0)
	{
		*s = c;
		s++;
		len--;
	}
	return (b);
}

// int main(void)
// {
//     char str[20] = "Hello, World!";
//     printf("Before memset: %s\n", str);

//     ft_memset(str, 'X', 5);

//     printf("After memset: %s\n", str);

//     return 0;
// }