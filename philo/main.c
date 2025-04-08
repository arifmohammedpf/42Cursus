/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:54:03 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 11:20:11 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		is_error;
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (print_error(1));
	is_error = init_all(&rules, argv);
	if (is_error != 0)
		return (print_error(is_error));
	if (launcher(&rules))
		return (print_error(3));
	return (0);
}
