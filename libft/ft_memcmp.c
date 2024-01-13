/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:39:38 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 09:45:03 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*tmp_s1 != *tmp_s2)
			return (*tmp_s1 - *tmp_s2);
		tmp_s1++;
		tmp_s2++;
		n--;
	}
	return (0);
}

// int main(void)
// {
//     const char str1[] = "Hello, World!";
//     const char str2[] = "Hello, Universe!";
//     size_t len = 4;

//     int result = ft_memcmp(str1, str2, len);

//     if (result == 0)
//     {
//         printf("str1 is equal to str2\n");
//     }
//     else
//     {
//         printf("str1 is not equal to str2\n");
//     }

//     return 0;
// }