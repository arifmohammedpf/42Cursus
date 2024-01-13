/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_create_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:28:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/24 20:15:29 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/push_swap.h"

/* free_array free the memory allocated to the string created from ft_split */
void	free_array(char **str)
{
	char	**new;
	int		len;
	int		i;

	new = str;
	len = 0;
	while (*new ++)
		len++;
	i = 0;
	while (i < len)
		free(str[i++]);
	free(str);
}

void	free_list_exit(t_list *stack, char **str)
{
	free_array(str);
	freelist(stack);
	print_error_exit();
}

/* Check number verify if the number is wether a zero or not, if the number is 
zero check number iterates over the string to verify if it is a valid 
zero or an error coming from atoi. */
int	check_number(int number, char *str)
{
	if (number == 0)
	{
		while (*str)
		{
			if (*str == '-' || *str == '+')
				str++;
			while (*str == '0')
				str++;
			if (*str)
				return (0);
		}
		return (1);
	}
	return (1);
}

/* create_stack function iterates over the input, converts the string
into an integer and assigns its value to the content variable.
Then creates a new node and assign the content variable as its data value.
Lastly, insert the new node as the last node on the stack. */
t_list	*create_stack(char **input)
{
	t_list	*stack;
	t_list	*node;
	char	**tmp;
	int		number;
	int		i;

	stack = NULL;
	while (*(++input))
	{
		tmp = ft_split(*input, ' ');
		if (!*tmp)
			free_list_exit(stack, tmp);
		i = -1;
		while (tmp[++i])
		{
			number = ps_atoi(tmp[i]);
			if (!(check_number(number, tmp[i])))
				free_list_exit(stack, tmp);
			node = ft_lstnew(number);
			ft_lstadd_back(&stack, node);
		}
		free_array(tmp);
	}
	return (stack);
}
