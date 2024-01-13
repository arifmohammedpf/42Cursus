/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:19:06 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/17 18:52:03 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// void	del(void	*item)
// {
// 	item = "NULL";
// }
// int main(void)
// {
//     t_list *node1 = ft_lstnew("node 1");
//     t_list *node2 = ft_lstnew("node 2");
//     t_list *node3 = ft_lstnew("node 3");

//     ft_lstadd_back(&node1, node2);
//     ft_lstadd_back(&node1, node3);

//     ft_lstiter(node1, &del);

// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);

//     return 0;
// }