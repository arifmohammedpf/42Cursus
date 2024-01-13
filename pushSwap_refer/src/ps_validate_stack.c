/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:28:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/24 17:17:25 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/push_swap.h"

int	no_duplicates(t_list *stack)
{
	t_list	*i;
	t_list	*j;
	int		flag;

	i = stack;
	while (i)
	{
		flag = 0;
		j = stack;
		while (j)
		{
			if (i->data == j->data)
				flag++;
			if (flag > 1)
				return (0);
			j = j->next;
		}
		i = i->next;
	}
	return (1);
}

int	is_unsorted(t_list *stack)
{
	t_list	*i;
	t_list	*j;

	i = stack;
	while (i->next)
	{
		j = i->next;
		while (j)
		{
			if (i->data > j->data)
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

int	validate_path(t_list *stack)
{
	if (!no_duplicates(stack))
	{
		freelist(stack);
		print_error_exit();
	}
	if (!is_unsorted(stack))
	{
		freelist(stack);
		exit(0);
	}
	return (1);
}
