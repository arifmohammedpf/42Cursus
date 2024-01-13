/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:14:24 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/07 10:35:44 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_splits(char **splits)
{
	int	j;

	j = 0;
	while (splits[j])
	{
		free(splits[j]);
		j++;
	}
	free(splits);
}

char	**ft_free_failed(char **str, int i)
{
	int	j;

	j = i;
	while (j >= 0)
	{
		if (str[j] == NULL)
		{
			while (i >= 0)
			{
				if (str[i] != NULL)
					free(str[i]);
				i--;
			}
			free(str);
			return (NULL);
		}
		j--;
	}
	return (str);
}

size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	size_t	len;
	char	**split_str;

	if (!s)
		return (0);
	split_str = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split_str)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			split_str[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	split_str[i] = NULL;
	return (ft_free_failed(split_str, i - 1));
}
