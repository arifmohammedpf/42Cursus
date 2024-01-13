/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:40:45 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/19 12:34:29 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>
// int main(void)
// {
//     t_list *node1 = ft_lstnew("node1");
//     t_list *node2 = ft_lstnew("node2");
//     t_list *node3 = ft_lstnew("node3");

//     ft_lstadd_front(&node1, node2);
//     ft_lstadd_front(&node1, node3);

//     t_list *last = ft_lstlast(node3);

//     printf("Last element content: %s\n", last->content);

//     free(last);
//     free(node2);
//     free(node3);

//     return 0;
// }