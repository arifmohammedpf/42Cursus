/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:01:02 by arimoham          #+#    #+#             */
/*   Updated: 2025/06/13 17:01:31 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_n_open(const char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (filename[len - 4] != '.' || filename[len - 3] != 'c' || filename[len
			- 2] != 'u' || filename[len - 1] != 'b')
	{
		printf("Error: File must have a .cub extension\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could not open file %s\n", filename);
		return (-1);
	}
	return (fd);
}

int	parse_cub_file(const char *filename, t_map_data *data)
{
	char	*line;
	int		fd;

	fd = validate_n_open(filename);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_line(data, line) == 0)
		{
			free(line);
			gnl_cleanup_static();
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_map_data(data));
}
