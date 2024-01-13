/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:33:43 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:24:06 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && n != 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		n--;
	}
	return (0);
}

// int main(void)
// {
//     const char *str1 = "Hello";
//     const char *str2 = "Hellp";
//     size_t n = 4;

//     int result = ft_strncmp(str1, str2, n);

//     if (result == 0)
//     {
//          printf("str1 is equal to str2\n");
//     }
//     else
//     {
//         printf("str1 is not equal to str2\n");
//     }

//     return 0;
// }