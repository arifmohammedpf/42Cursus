/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:49:13 by arimoham          #+#    #+#             */
/*   Updated: 2023/12/21 08:11:09 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_after_nl(char *curr_buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (curr_buffer[i] != '\n' && curr_buffer[i])
		i++;
	if (curr_buffer[i] == '\n')
		i++;
	if (!curr_buffer[i])
		return (free(curr_buffer), NULL);
	new_buffer = ft_strdup(curr_buffer + i);
	if (!new_buffer)
		return (free(curr_buffer), NULL);
	return (free(curr_buffer), new_buffer);
}

char	*save_new_line(char *curr_buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (curr_buffer[i] != '\n' && curr_buffer[i])
		i++;
	if (curr_buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char *) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (curr_buffer[i] && curr_buffer[i] != '\n')
	{
		line[i] = curr_buffer[i];
		i++;
	}
	if (curr_buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_buffer(char *curr_buffer, char *tmp_buffer, int fd, ssize_t *byte)
{
	char	*tmp_free;

	while (*byte > 0 && !ft_strchr(curr_buffer, '\n'))
	{
		*byte = read(fd, tmp_buffer, BUFFER_SIZE);
		if (*byte <= 0)
		{
			free(tmp_buffer);
			if (*byte == -1)
				return (free(curr_buffer), NULL);
			return (curr_buffer);
		}
		tmp_buffer[*byte] = '\0';
		tmp_free = curr_buffer;
		curr_buffer = ft_strjoin(curr_buffer, tmp_buffer);
		free(tmp_free);
	}
	return (free(tmp_buffer), curr_buffer);
}

char	*read_buffer_line(char *curr_buffer, int fd)
{
	ssize_t	byte;
	char	*tmp_buffer;

	byte = 1;
	tmp_buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (tmp_buffer == NULL)
		return (NULL);
	curr_buffer = read_buffer(curr_buffer, tmp_buffer, fd, &byte);
	return (curr_buffer);
}

char	*get_next_line(int fd)
{
	static char	*curr_buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	curr_buffer[fd] = read_buffer_line(curr_buffer[fd], fd);
	if (!curr_buffer[fd])
		return (NULL);
	line = save_new_line(curr_buffer[fd]);
	curr_buffer[fd] = save_after_nl(curr_buffer[fd]);
	return (line);
}
