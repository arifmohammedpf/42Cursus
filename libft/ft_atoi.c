/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:48:16 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/20 14:35:28 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_llong(int sign, unsigned long long j)
{
	if (sign == -1 && j > LLONG_MAX)
		return (0);
	if (sign == 1 && j > LLONG_MAX)
		return (-1);
	return (1);
}

int	ft_isspace(int c)
{
	if ((c == ' ' || c == '\t' || c == '\v'
			|| c == '\n' || c == '\f' || c == '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long	j;
	size_t				i;
	int					sign;

	i = 0;
	j = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (check_llong(sign, j) != 1)
			return (check_llong(sign, j));
		j = (j * 10) + (str[i++] - '0');
	}
	if (check_llong(sign, j) != 1)
		return (check_llong(sign, j));
	return (sign * j);
}

// int	main(void)
// {
// 	printf("my llong max -> %d\n", ft_atoi("9223372036854775807"));
// 	printf("og llong max -> %d\n", atoi("9223372036854775807"));
// 	printf("my greater than llong max -> %d\n", ft_atoi("9223372036854775809"));
// 	printf("og greater than llong max -> %d\n", atoi("9223372036854775809"));
// 	printf("my llong min -> %d\n", ft_atoi("-9223372036854775808"));
// 	printf("og llong min -> %d\n", atoi("-9223372036854775808"));
// 	printf("my int min -> %d\n", ft_atoi("-2147483648"));
// 	printf("og int min -> %d\n", atoi("-2147483648"));
// 	printf("my greater than int min -> %d\n", ft_atoi("-2147483649"));
// 	printf("og greater than int min -> %d\n", atoi("-2147483649"));
// 	printf("my int max -> %d\n", ft_atoi("2147483647"));
// 	printf("og int max -> %d\n", atoi("2147483647"));
// 	printf("my greater than int max -> %d\n", ft_atoi("2147483649"));
// 	printf("og greater than int max -> %d\n", atoi("2147483649"));
// 	printf("my long min -> %d\n", ft_atoi("-2147483648"));
// 	printf("og long min -> %d\n", atoi("-2147483648"));
// 	printf("my greater than long min -> %d\n", ft_atoi("-2147483649"));
// 	printf("og greater than long min -> %d\n", atoi("-2147483649"));
// 	printf("my long max -> %d\n", ft_atoi("2147483647"));
// 	printf("og long max -> %d\n", atoi("2147483647"));
// 	printf("my greater than long max -> %d\n", ft_atoi("2147483649"));
// 	printf("og greater than long max -> %d\n", atoi("2147483649"));
// }
