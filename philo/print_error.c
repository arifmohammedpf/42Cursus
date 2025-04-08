/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:54:21 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/13 15:12:36 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, "Error: ", 7);
	write(1, str, len);
	write(1, "\n", 1);
	return (1);
}

int	print_error(int error)
{
	if (error == 1)
		return (ft_error("Incorrect arguments"));
	if (error == 2)
		return (ft_error("Mutex initialization failed"));
	if (error == 3)
		return (ft_error("Creating threads failed"));
	return (1);
}
