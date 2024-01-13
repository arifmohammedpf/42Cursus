/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:38:02 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 09:47:51 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
	return ;
}

// void myprint(unsigned int index, char *c)
// {
//     printf("Index: %d, Character: %c\n", index, *c);
// }

// int main(void)
// {
//     char str[] = "Hello";
//     ft_striteri(str, &myprint);

//     return 0;
// }