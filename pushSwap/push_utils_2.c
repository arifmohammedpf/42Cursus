
#include "push_swap.h"

int is_sorted(t_list *a)
{
	t_list	*i;
	t_list	*j;

	i = a;
	while (i->next)
	{
		j = i->next;
		while (j)
		{
			if (i->value > j->value)
				return (0);
			j = j->next;
		}
		i = i->next;
	}
	free_list(a);
	return (1);
}

void	normal_sort(t_list **list)
{
	t_list	*i;
	t_list	*j;
	int		tmp;

	i = *list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->value > j->value)
			{
				tmp = i->value;
				i->value = j->value;
				j->value = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

void	make_index_value(t_list *a, t_list *clone)
{
	int		index;
	t_list	*tmp;

	while (a)
	{
		index = 0;
		tmp = clone;
		while (tmp)
		{
			if (a->value == tmp->value)
			{
				a->value = index;
				break ;
			}
			tmp = tmp->next;
			index++;
		}
		a = a->next;
	}
}