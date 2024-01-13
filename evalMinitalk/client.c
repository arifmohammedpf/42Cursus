/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtashrif <mtashrif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:01 by mtashrif          #+#    #+#             */
/*   Updated: 2023/12/01 16:43:04 by mtashrif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_messege(char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i--;
	}
}

int	check_pid(int pid, char *av)
{
	if (pid <= 0)
	{
		write(1, "Invalid pid", 11);
		return (0);
	}
	if (ft_isalpha(av) == 1)
	{
		write(1, "Do not add letters with PID", 26);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (check_pid(pid, av[1]) == 0)
			return (0);
		while (av[2][i] != '\0')
			send_messege(av[2][i++], pid);
		exit(0);
	}
	else
		exit(1);
	return (0);
}
