/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:25:20 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/27 07:35:41 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str_arg)
{
	int	count;

	count = 0;
	if (!str_arg)
	{
		write(1, "(null)", 6);
		count = 6;
		return (count);
	}
	while (*str_arg != '\0')
	{
		count += ft_print_char(*str_arg);
		str_arg++;
	}
	return (count);
}

int	ft_print_char(char c_arg)
{
	write(1, &c_arg, 1);
	return (1);
}

int	ft_print_nbr(int nbr_arg)
{
	int	count;

	count = 0;
	if (nbr_arg == -2147483648)
	{
		write(1, "-2147483648", 11);
		count = 11;
	}
	else if (nbr_arg < 0)
	{
		write(1, "-", 1);
		count++;
		count += ft_print_nbr(-nbr_arg);
	}
	else
	{
		if (nbr_arg > 9)
			count += ft_print_nbr(nbr_arg / 10);
		count += ft_print_char(nbr_arg % 10 + '0');
	}
	return (count);
}
