/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:36:30 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 10:32:01 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int value)
{
	t_list	*lptr;

	lptr = (t_list *)malloc(sizeof(t_list));
	if (!lptr)
		return (NULL);
	lptr->value = value;
	lptr->next = NULL;
	return (lptr);
}
