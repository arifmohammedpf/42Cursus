/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:16:58 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 19:51:52 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*s;
	int		len;
	int		n;

	n = nbr;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_nbrlen(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (n < 0)
		n = -nbr;
	while (len > 0)
	{
		len--;
		s[len] = (n % 10) + '0';
		n = n / 10;
	}
	if (nbr < 0)
		s[0] = '-';
	return (s);
}

// int	main(void)
// {
// 	printf("ft - %s", ft_itoa(0));
// }
