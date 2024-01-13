/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:56:51 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 15:04:09 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	is_error_zero(int input, char *str)
{
	int	i;

	i = 0;
	if (input == 0)
	{
		while (str[i])
		{
			if ((str[i] == '-' || str[i] == '+')
				&& (str[i + 1] && str[i + 1] >= '0' && str[i + 1] <= '9'))
				i++;
			while (str[i] == '0')
				i++;
			if (str[i])
				return (1);
		}
		return (0);
	}
	return (0);
}

int	is_dup(int input, t_list *head)
{
	t_list	*tmp_list;

	tmp_list = head;
	while (tmp_list)
	{
		if (tmp_list->value == input)
			return (1);
		tmp_list = tmp_list->next;
	}
	return (0);
}

void	free_list(t_list *list)
{
	t_list	*tmp_list;

	tmp_list = list;
	while (tmp_list)
	{
		tmp_list = tmp_list->next;
		free(list);
		list = tmp_list;
	}
}

void	exit_push_swap(t_list *head, char **splits)
{
	free_splits(splits);
	free_list(head);
	ft_putstr("Error\n");
	exit(1);
}

int	get_list_stack(char **args, t_list **head)
{
	t_list	*node;
	char	**tmp_splits;
	int		input;
	int		i;
	int		j;

	i = 0;
	*head = NULL;
	while (args[++i])
	{
		tmp_splits = ft_split(args[i], ' ');
		if (!tmp_splits)
			return (0);
		j = -1;
		while (tmp_splits[++j])
		{
			input = ft_atoi(tmp_splits[j]);
			if (is_error_zero(input, tmp_splits[j]) || is_dup(input, *head))
				exit_push_swap(*head, tmp_splits);
			node = ft_lstnew(input);
			ft_lstadd_back(head, node);
		}
		free_splits(tmp_splits);
	}
	return (1);
}

// t_list	*get_list_stack(char **args)
// {
// 	t_list	*head;
// 	t_list	*node;
// 	char	**tmp_splits;
// 	int		input;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	head = NULL;
// 	while (args[++i])
// 	{
// 		tmp_splits = ft_split(args[i], ' ');
// 		if (!tmp_splits)
// 			return (NULL);
// 		j = -1;
// 		while (tmp_splits[++j])
// 		{
// 			input = ft_atoi(tmp_splits[j]);
// 			if (is_error_zero(input, tmp_splits[j]))
// 				exit_push_swap(head, tmp_splits);
// 			node = ft_lstnew(input);
// 			ft_lstadd_back(&head, node);
// 			printf("int=> %d\n", head->value);
// 		}
// 		free_splits(tmp_splits);
// 	}
// 	return (head);
// }