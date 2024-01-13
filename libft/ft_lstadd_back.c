/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:01:07 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/17 18:32:46 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_list;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last_list = ft_lstlast(*lst);
		last_list->next = new;
	}
	else
		*lst = new;
}

// #include <stdio.h>
// int main(void)
// {
//     t_list *node1 = ft_lstnew("test1");
//     t_list *node2 = ft_lstnew("test2");
//     t_list *node3 = ft_lstnew("test3");

// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);

// 	while (node1)
// 	{
// 		printf("%s\n", node1->content);
// 		node1 = node1->next;
// 	}
// 	free(node1);
// 	free(node2);
// 	free(node3);

//     return 0;
// }