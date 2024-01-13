/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:04:00 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/27 07:34:54 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned_decimal(unsigned int nbr_arg)
{
	int	count;

	count = 0;
	if (nbr_arg > 9)
		count += ft_print_nbr(nbr_arg / 10);
	count += ft_print_char(nbr_arg % 10 + '0');
	return (count);
}

int	ft_print_hexa_decimal(unsigned int nbr_arg, char x)
{
	int		count;
	char	str[30];
	char	*hex_char;
	int		i;
	int		char_idx;

	count = 0;
	if (nbr_arg == 0)
		return (ft_print_char('0'));
	if (x == 'x')
		hex_char = "0123456789abcdef";
	else
		hex_char = "0123456789ABCDEF";
	i = 0;
	while (nbr_arg != 0)
	{
		char_idx = nbr_arg % 16;
		str[i++] = hex_char[char_idx];
		nbr_arg = nbr_arg / 16;
	}
	i--;
	while (i >= 0)
		count = count + ft_print_char(str[i--]);
	return (count);
}

int	ft_print_pointer(size_t ptr_arg)
{
	int		count;
	char	str[30];
	char	*ptr_char;
	int		i;
	int		ptr_idx;

	write(1, "0x", 2);
	count = 2;
	if (ptr_arg == 0)
		return (ft_print_char('0') + count);
	ptr_char = "0123456789abcdef";
	i = 0;
	while (ptr_arg != 0)
	{
		ptr_idx = ptr_arg % 16;
		str[i++] = ptr_char[ptr_idx];
		ptr_arg = ptr_arg / 16;
	}
	i--;
	while (i >= 0)
		count = count + ft_print_char(str[i--]);
	return (count);
}

int	print_arg(char *str, va_list *args)
{
	if (*str == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (*str == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (*str == 'd' || *str == 'i')
		return (ft_print_nbr(va_arg(*args, int)));
	else if (*str == 'u')
		return (ft_print_unsigned_decimal(va_arg(*args, unsigned int)));
	else if (*str == 'x' || *str == 'X')
		return (ft_print_hexa_decimal(va_arg(*args, unsigned int), *str));
	else if (*str == 'p')
		return (ft_print_pointer(va_arg(*args, size_t)));
	else
		return (ft_print_char(*str));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		char_count;

	va_start(args, str);
	char_count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			char_count += print_arg((char *)str, &args);
		}
		else
			char_count += ft_print_char(*str);
		str++;
	}
	va_end(args);
	return (char_count);
}
