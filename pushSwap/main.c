/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:56:40 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/31 08:34:13 by arimoham         ###   ########.fr       */
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

void	error_exit()
{
	ft_putstr("Error\n");
	exit(1);
}

int	main(int count, char **args)
{
	t_list	*a;
	t_list	*b;
	t_list	*clone;

	b = NULL;
	if (count == 1)
		return (0);
	if (args[1] == NULL || !is_valid_args(args))
		error_exit();
	if (!get_list_stack(args, &a))
		return (free_list(a), 0);
	if (!get_list_stack(args, &clone))
		return (free_list(a), free_list(clone), 0);
	if (!is_sorted(a))
	{
		normal_sort(&clone);
		make_index_value(a, clone);
		sort_stack(&a, &b);
	}
	free_list(clone);
	free_list(a);
	return (0);
}
