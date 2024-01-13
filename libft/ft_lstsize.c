/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:28:02 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/17 18:18:06 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// #include "stdio.h"
// int main(void)
// {
//     // Create some elements
// 	t_list *head = ft_lstnew("test0");
//     t_list *node1 = ft_lstnew("test1");
//     t_list *node2 = ft_lstnew("test2");
//     t_list *node3 = ft_lstnew("test3");

// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	ft_lstadd_back(&head, node3);

// 	printf("size is %d\n", ft_lstsize(head));

// 	free(head);
// 	free(node1);
// 	free(node2);
// 	free(node3);
//     return 0;
// }