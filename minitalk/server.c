/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:59:04 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/28 09:00:43 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	get_signal(int signal)
{
	static char	char_signal;
	static int	bits = 0;

	if (signal == SIGUSR1)
		char_signal = (char_signal << 1) | 0;
	if (signal == SIGUSR2)
		char_signal = (char_signal << 1) | 1;
	bits++;
	if (bits == 8)
	{
		ft_putchar(char_signal);
		char_signal = 0;
		bits = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr("Server started at PID: ");
	ft_putnbr(pid);
	ft_putchar('\n');
	signal(SIGUSR1, get_signal);
	signal(SIGUSR2, get_signal);
	while (1)
		;
}
