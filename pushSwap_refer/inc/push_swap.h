/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:16:08 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/21 23:31:35 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../inc/libft.h"

t_list	*create_stack(char **list_of_numbers);
void	push_swap(t_list **stack_a, t_list **stack_b);
int		ps_atoi(const char *str);
void	index_stack(t_list *unsorted, t_list *sorted);
void	sortlist(t_list **list);
void	freelist(t_list *list);
int		validate_path(t_list *stack);
void	print_error_exit(void);

void	ra(t_list **stack_a);
void	rra(t_list **stack_a);
void	pb(t_list **stack_a, t_list **stack_b);
void	pa(t_list **stack_a, t_list **stack_b);
void	sa(t_list **stack_a);

#endif