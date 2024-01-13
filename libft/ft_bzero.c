/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:51:28 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/09 07:26:06 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t size)
{
	ft_memset(s, '\0', size);
}

// int main(void)
// {
// 	char str[110] = "aasdasdasd";
// 	ft_bzero(str, 4);
// 	printf("%s", str);
// }