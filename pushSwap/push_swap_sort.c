/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:28:08 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 20:32:33 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	three_numbers_sort(t_list **a)
{
  int v1;
  int v2;
  int v3;

  v1 = (*a)->value;
  v2 = (*a)->next->value;
  v3 = (*a)->next->next->value;

	if ((v1 < v2) && (v1 < v3))
	{
		rra_or_rrb(a, 'a');
		sa_or_sb(a, 'a');
	}
	else if ((v1 < v2) && (v1 > v3))
		rra_or_rrb(a, 'a');
	else if ((v1 > v2) && (v1 < v3))
		sa_or_sb(a, 'a');
	else if ((v1 > v2) && (v2 < v3))
		ra_or_rb(a, 'a');
	else
	{
		sa_or_sb(a, 'a');
		rra_or_rrb(a, 'a');
	}
}

void	four_numbers_sort(t_list **a, t_list **b)
{
	int	i;

	i = 4;
	while (i--)
	{
		if ((*a)->value == 0)
    {
			pb(a, b);
      break;
    }
		else
			ra_or_rb(a, 'a');
	}
	three_numbers_sort(a);
	pa(a, b);
}

void	five_numbers_sort(t_list **a, t_list **b)
{
	int	i;

	i = 5;
	while (i--)
	{
		if ((*a)->value == 0 || (*a)->value == 4)
			pb(a, b);
		else
			ra_or_rb(a, 'a');
	}
	three_numbers_sort(a);
	pa(a, b);
	pa(a, b);
	if ((*a)->value == 0)
  {
		sa_or_sb(a, 'a');
		ra_or_rb(a, 'a');
	}
	else
		ra_or_rb(a, 'a');
}

void	numbers_sort(t_list **a, t_list **b, int size)
{
	int	j;
	int min;
	int min_idx;

	min = 0;
	min_idx = 0;
	j = 0;
	while (size > j++)
	{
		if ((*a)->value < min)
		{
			min = (*a)->value;
			min_idx = j - 1;
		}
	}
	while (*a != NULL)
	{
		if ((*a)->value == min)
		{
			pb(a, b);
			if (*a != NULL)
			{
				j = 0;
				min = (*a)->value;
				while (size > j++)
				{
					if ((*a)->value < min)
					{
						min = (*a)->value;
						min_idx = j - 1;
					}
				}
			}
		}
		else
		{
			if (min_idx < (size / 2))
				rra_or_rrb(a, 'a');
			else
				ra_or_rb(a, 'a');
		}
	}
	while (*b != NULL)
		pa(a, b);
}

void	sort_stack(t_list **a, t_list **b)
{
	int	size;

	size = ft_lstsize(*a);
	if (size == 2)
	  sa_or_sb(a, 'a');
	else if (size == 3)
		three_numbers_sort(a);
	else if (size == 4)
		four_numbers_sort(a, b);
	else if (size == 5)
		five_numbers_sort(a, b);
	else
		numbers_sort(a, b, size);
}