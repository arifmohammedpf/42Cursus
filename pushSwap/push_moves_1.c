/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_moves_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:18:44 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/31 17:55:43 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa_or_sb(t_list **a, char swap_type)
{
	int	tmp;

	if (!(*a) || ft_lstsize(*a) == 1)
		return ;
	tmp = (*a)->value;
	(*a)->value = (*a)->next->value;
	(*a)->next->value = tmp;
	if (swap_type == 'a')
		write(1, "sa\n", 3);
	else
		write(1, "sb\n", 3);
}

void	ss(t_list **a, t_list **b)
{
	int	tmp;

	if (!(*a) || ft_lstsize(*a) == 1 || !(*b) || ft_lstsize(*b) == 1)
		return ;
	tmp = (*a)->value;
	(*a)->value = (*a)->next->value;
	(*a)->next->value = tmp;
	tmp = (*b)->value;
	(*b)->value = (*b)->next->value;
	(*b)->next->value = tmp;
	write(1, "ss\n", 3);
}

void	pa(t_list **a, t_list **b)
{
	t_list	*tmp;
	t_list	*node;

	if (!(*b))
		return ;
	tmp = *b;
	node = ft_lstnew(tmp->value);
	*b = tmp->next;
	ft_lstadd_front(a, node);
	free(tmp);
	write(1, "pa\n", 3);
}

void	pb(t_list **a, t_list **b)
{
	t_list	*tmp;
	t_list	*node;

	if (!(*a))
		return ;
	tmp = *a;
	node = ft_lstnew(tmp->value);
	*a = tmp->next;
	ft_lstadd_front(b, node);
	free(tmp);
	write(1, "pb\n", 3);
}
