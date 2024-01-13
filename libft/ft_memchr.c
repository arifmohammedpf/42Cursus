/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:36:49 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:04:39 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s2;
	size_t	i;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		if (s2[i] == (char)c)
			return (&s2[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	ft_memchr("aca", 'c', 2);
// }
