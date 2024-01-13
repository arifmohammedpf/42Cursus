/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:33:45 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 09:48:52 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	size_t	i;

	if (s && f)
	{
		s2 = ft_strdup(s);
		if (!s2)
			return (NULL);
		i = 0;
		while (s2[i])
		{
			s2[i] = (*f)(i, s2[i]);
			i++;
		}
		return (s2);
	}
	return (NULL);
}

// char modify(unsigned int index, char c)
// {
//     return c + index;
// }

// int main(void)
// {
//     const char *str = "hello, world!";
//     char *result = ft_strmapi(str, &modify);

//     printf("Original: %s\n", str);
// 	printf("Modified: %s\n", result);
// 	free(result);
//     return 0;
// }