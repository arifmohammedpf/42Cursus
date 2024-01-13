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

	b = NULL;
	if (count == 1)
		return (0);
	if (!get_list_stack(args, &a))
	{
		ft_putstr("Error\n");
		exit(1);
	}
	sort_stack(a, b);
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