/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:58:54 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/28 09:01:58 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(char c, int pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		bit--;
	}
}

int	main(int count, char **args)
{
	int	i;
	int	pid;

	i = 0;
	if (count == 3)
	{
		if (ft_isalpha(args[1]))
		{
			ft_putstr("Pid must be a number");
			return (0);
		}
		pid = ft_atoi(args[1]);
		if (pid <= 0)
		{
			ft_putstr("Enter a valid pid");
			return (0);
		}
		while (args[2][i] != '\0')
		{
			send_char(args[2][i], pid);
			i++;
		}
	}
	return (0);
}
