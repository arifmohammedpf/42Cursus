/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:38:41 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/20 14:48:02 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;

	if (!f || !lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&node, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}

// #include <stdio.h>
// void	del(void	*item)
// {
// 	item = "NULL";
// }
// void	*editContent(void	*item)
// {
// 	item = item + 2;
// 	return (item);
// }
// int main(void)
// {
//     t_list *node1 = ft_lstnew("node 1");
//     t_list *node2 = ft_lstnew("node 2");
//     t_list *node3 = ft_lstnew("node 3");

//     ft_lstadd_back(&node1, node2);
//     ft_lstadd_back(&node1, node3);

//     t_list *mappedList = ft_lstmap(node1, &editContent, &del);

// 	while (mappedList)
// 	{
// 		printf("%s\n",mappedList->content);
// 		mappedList = mappedList->next;
// 	}

//     return 0;
// }