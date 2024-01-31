/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_moves_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:19:05 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/31 17:55:29 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_or_rb(t_list **a, char swap_type)
{
	t_list	*tmp;
	t_list	*last;

	if (!(*a) || ft_lstsize(*a) == 1)
		return ;
	tmp = *a;
	last = ft_lstlast(*a);
	*a = (*a)->next;
	tmp->next = NULL;
	last->next = tmp;
	if (swap_type == 'a')
		write(1, "ra\n", 3);
	else
		write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b)
{
	t_list	*tmp_a;
	t_list	*last_a;
	t_list	*tmp_b;
	t_list	*last_b;

	if (!(*a) || ft_lstsize(*a) == 1 || !(*b) || ft_lstsize(*b) == 1)
		return ;
	tmp_a = *a;
	last_a = ft_lstlast(*a);
	*a = (*a)->next;
	tmp_a->next = NULL;
	last_a->next = tmp_a;
	tmp_b = *b;
	last_b = ft_lstlast(*b);
	*b = (*b)->next;
	tmp_b->next = NULL;
	last_b->next = tmp_b;
	write(1, "rr\n", 3);
}

void	rra_or_rrb(t_list **a, char swap_type)
{
	t_list	*tmp;
	t_list	*last;

	if (!(*a) || ft_lstsize(*a) == 1)
		return ;
	tmp = *a;
	last = ft_lstlast(*a);
	while (tmp->next != last)
		tmp = tmp->next;
	tmp->next = NULL;
	last->next = *a;
	*a = last;
	if (swap_type == 'a')
		write(1, "rra\n", 4);
	else
		write(1, "rrb\n", 4);
}
