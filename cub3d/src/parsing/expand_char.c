/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:50:29 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/19 14:55:19 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_tabs_in_line(char *line)
{
	int	i;
	int	tab_count;

	if (!line)
		return (0);
	tab_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			tab_count++;
		i++;
	}
	return (tab_count);
}

static char	*allocate_expanded_line(char *line, int tab_count)
{
	char	*expanded;
	int		new_len;

	if (!line)
		return (NULL);
	new_len = ft_strlen(line) + (tab_count * 3);
	expanded = malloc(new_len + 1);
	if (!expanded)
		return (NULL);
	return (expanded);
}

static void	fill_expanded_line(char *line, char *expanded)
{
	int	i;
	int	j;

	if (!line || !expanded)
		return ;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			expanded[j++] = ' ';
			expanded[j++] = ' ';
			expanded[j++] = ' ';
			expanded[j++] = ' ';
		}
		else
		{
			expanded[j++] = line[i];
		}
		i++;
	}
	expanded[j] = '\0';
}

char	*expand_tabs_to_spaces(char *line)
{
	char	*expanded;
	int		tab_count;

	if (!line)
		return (NULL);
	tab_count = count_tabs_in_line(line);
	expanded = allocate_expanded_line(line, tab_count);
	if (!expanded)
		return (NULL);
	fill_expanded_line(line, expanded);
	return (expanded);
}
