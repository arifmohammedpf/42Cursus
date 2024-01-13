/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:13:36 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/19 12:34:18 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int main(void)
// {    
//     t_list *node1 = ft_lstnew("Arif");
//     t_list *node2 = ft_lstnew("Mohammed");
//     t_list *node3 = ft_lstnew("pf");

// 	ft_lstadd_front(&node1, node2);
// 	ft_lstadd_front(&node1, node3);

// 	while (node1)
// 	{
// 		printf("%s\n",node1->content);
// 		node1 = node1->next;
// 	}
// 	free(node1);
// 	free(node1);
// 	free(node2);

//     return 0;
// }