/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:48:16 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/27 14:06:58 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			n;

	num = 0;
	n = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '+' || *str == '-') && (*(str + 1)
			&& *(str + 1) >= '0' && *(str + 1) <= '9'))
	{
		if (*str == '-')
			n = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		if ((n == -1 && num * n < INT_MIN) || (n == 1 && num > INT_MAX))
			return (0);
		str++;
	}
	if ((*str && *str < '0') || (*str && *str > '9'))
		return (0);
	return (num * n);
}
