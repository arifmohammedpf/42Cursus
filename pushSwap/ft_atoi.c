/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:48:16 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 13:36:36 by arimoham         ###   ########.fr       */
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

int	check_sign(const char *str, int sign, size_t *i)
{
	if ((str[(*i)] == '-' || str[(*i)] == '+') && (str[(*i) + 1]
			&& str[(*i) + 1] >= '0' && str[(*i) + 1] <= '9'))
	{
		if (str[(*i)++] == '-')
			sign = sign * -1;
	}
	return (sign);
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
	sign = check_sign(str, sign, &i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (check_llong(sign, j) != 1)
			return (check_llong(sign, j));
		j = (j * 10) + (str[i++] - '0');
	}
	if (check_llong(sign, j) != 1)
		return (check_llong(sign, j));
	if ((str[i] && str[i] < '0') || (str[i] && str[i] > '9'))
		return (0);
	return (sign * j);
}
