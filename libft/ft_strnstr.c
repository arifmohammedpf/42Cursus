/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:42:46 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:27:57 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	int			needlen;
	char		*hay;
	char		*need;

	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	hay = (char *)haystack;
	need = (char *)needle;
	i = 0;
	needlen = ft_strlen(need);
	while (hay[i] != '\0' && (i + needlen) <= len)
	{
		if (ft_strncmp((hay + i), need, needlen) == 0)
		{
			return (hay + i);
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     const char *haystack = "Hello, World!";
//     const char *needle = "World";
//     size_t len = 13;

//     char *result = ft_strnstr(haystack, needle, len);

//     if (result != NULL)
//     {
//         printf("found: %s\n", result);
//     }
//     else
//     {
//         printf("Needle not found in the haystack.\n");
//     }

//     return 0;
// }