/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:56:40 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/27 09:26:33 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	is_valid_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '\0')
			return (0);
		while (args[i][j] && args[i][j] == ' ')
		{
			if (args[i][j + 1] == '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int count, char **args)
{
	t_list	*a;
	t_list	*b;
	t_list	*clone;

	b = NULL;
	if (count == 1)
		return (0);
	if (args[1] == NULL || !is_valid_args(args)
		|| !get_list_stack(args, &a) || !get_list_stack(args, &clone))
	{
		ft_putstr("Error\n");
		exit(1);
	}
	if (!is_sorted(a))
	{
		normal_sort(&clone);
		make_index_value(a, clone);
		free_list(clone);
		sort_stack(&a, &b);
	}
	return (0);
}
