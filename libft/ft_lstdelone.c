/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:09:34 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 18:00:58 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

// #include <stdio.h>
// void	del(void	*item)
// {
// 	item = 0;
// }
// int main(void)
// {
//     t_list *node1 = ft_lstnew("node1");
//     t_list *node2 = ft_lstnew("node2");
//     t_list *node3 = ft_lstnew("node3");

//     ft_lstadd_back(&node1, node2);
//     ft_lstadd_back(&node1, node3);

// 	printf("before - %s\n",node1->content);
// 	printf("before - %s\n",node2->content);
// 	printf("before - %s\n",node3->content);

//     ft_lstdelone(node1, &del);
// 	ft_lstdelone(node2, &del);
// 	ft_lstdelone(node3, &del);

// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);

//     return 0;
// }