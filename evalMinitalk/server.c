/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtashrif <mtashrif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:27 by mtashrif          #+#    #+#             */
/*   Updated: 2023/12/01 16:44:35 by mtashrif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_message(int sig)
{
	static int	n;
	static int	byte;

	if (sig == SIGUSR1)
		byte += 1 << (7 - n);
	if (sig == SIGUSR2)
		byte += 0 << (7 - n);
	n++;
	if (n == 8)
	{
		ft_putchar(byte);
		n = 0;
		byte = 0;
	}
}

int	main(void)
{
	ft_putstr("Server is live now \n");
	ft_putstr("PID is : ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	signal(SIGUSR1, receive_message);
	signal(SIGUSR2, receive_message);
	while (1)
		pause();
}
