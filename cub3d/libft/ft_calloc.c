/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:43:12 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/29 14:47:04 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	tlen;
	void	*ptr;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	tlen = count * size;
	ptr = malloc(tlen);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, tlen);
	return (ptr);
}
