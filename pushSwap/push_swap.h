/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 10:00:16 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/31 17:55:06 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

int		get_list_stack(char **args, t_list **a);

void	sa_or_sb(t_list **a, char swap_type);
void	ss(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);
void	ra_or_rb(t_list **a, char swap_type);
void	rr(t_list **a, t_list **b);
void	rra_or_rrb(t_list **a, char swap_type);

void	three_numbers_sort(t_list **a);
void	four_numbers_sort(t_list **a, t_list **b);
void	five_numbers_sort(t_list **a, t_list **b);
void	numbers_sort(t_list **a, t_list **b, int size);
void	sort_stack(t_list **a, t_list **b);

int		is_error_zero(int input, char *str);
int		is_dup(int input, t_list *head);
int		is_sorted(t_list *a);
void	free_list(t_list *list);
void	exit_push_swap(t_list *head, char **splits);
int		get_list_stack(char **args, t_list **head);
void	normal_sort(t_list **list);
void	make_index_value(t_list *a, t_list *clone);
int		get_max_value_bits(t_list *a);

#endif