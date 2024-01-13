/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:36:30 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/18 18:09:23 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lptr;

	lptr = (t_list *)malloc(sizeof(t_list));
	if (!lptr)
		return (NULL);
	lptr->content = content;
	lptr->next = NULL;
	return (lptr);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *node;

// 	node = ft_lstnew("hello");
// 	printf("%s\n",node->content);
// 	return(0);
// }