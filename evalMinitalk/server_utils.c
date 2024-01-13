/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtashrif <mtashrif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:20 by mtashrif          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:21 by mtashrif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	else
		write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int d)
{
	if (d == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (d < 0)
	{
		ft_putchar('-');
		d = -d;
	}
	if (d >= 0 && d <= 9)
		ft_putchar(d + '0');
	if (d > 9)
	{
		ft_putnbr(d / 10);
		ft_putnbr(d % 10);
	}
}
