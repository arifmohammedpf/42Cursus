/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:05:39 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 11:56:07 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lptr;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		lptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lptr;
	}
}

// #include <stdio.h>
// void	del(void	*item)
// {
// 	item = 0;
// }
// int main(void)
// {
//     t_list *node1 = ft_lstnew("node 1");
//     t_list *node2 = ft_lstnew("node 2");
//     t_list *node3 = ft_lstnew("node 3");

//     ft_lstadd_back(&node1, node2);
//     ft_lstadd_back(&node1, node3);

// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);
//     ft_lstclear(&node1, &del);

// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);

//     return 0;
// }