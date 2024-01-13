/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_freelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:57:36 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/24 16:51:33 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	freelist(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		tmp = tmp->next;
		free(list);
		list = tmp;
	}
}
