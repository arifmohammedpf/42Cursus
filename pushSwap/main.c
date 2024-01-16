/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:56:40 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 20:33:41 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	main(int count, char **args)
{
	t_list	*a;
	t_list	*b;
	t_list	*clone;

	b = NULL;
	if (count == 1)
		return (0);
	if (args[1] == NULL || !args[1][0]
		|| !get_list_stack(args, &a) || !get_list_stack(args, &clone))
	{
		ft_putstr("Error\n");
		exit(1);
	}
	normal_sort(&clone);
	make_index_value(a, clone);
	free_list(clone);
	sort_stack(&a, &b);
	ft_lstprint(a);
	return (0);
}

// int	main(int count, char **args)
// {
// 	t_list	*a;

// 	if (count == 1)
// 		return (0);
// 	a = get_list_stack(args);
// 	if (!a)
// 	{
// 		ft_putstr("Error\n");
// 		exit(1);
// 	}
// 	ft_lstprint(a);
// 	return (0);	
// }