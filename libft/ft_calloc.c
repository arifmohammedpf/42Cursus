/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:46:48 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/19 12:08:13 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s1;

	if (count >= INT_MAX || size >= INT_MAX)
		return (NULL);
	s1 = (void *)malloc(count * size);
	if (!s1)
		return (NULL);
	ft_bzero(s1, count * size);
	return (s1);
}

// int main(void)
// {
//     int *arr = (int *)ft_calloc(2147483647, 2147483647);

//     // for (size_t i = 0; i < 5; i++)
// 	// {
// 	// 	printf("%d ", arr[i]);
// 	// }
//     return 0;
// }