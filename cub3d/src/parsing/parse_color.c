/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:57 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/10 11:43:02 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_rgb_component(char *component, int index, t_rgb *color)
{
	char	*trimmed;
	int		value;

	trimmed = ft_strtrim(component, " \t");
	if (!trimmed || !trimmed[0])
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	if (!is_valid_number(trimmed))
	{
		free(trimmed);
		return (0);
	}
	value = ft_atoi(trimmed);
	free(trimmed);
	if (index == 0)
		color->r = value;
	else if (index == 1)
		color->g = value;
	else
		color->b = value;
	return (1);
}

static int	count_components(char **rgb)
{
	int	count;

	count = 0;
	while (rgb[count])
		count++;
	return (count);
}

static int	validate_color_format(char *color_str)
{
	int	comma_count;
	int	i;

	comma_count = 0;
	i = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
	{
		printf("Error: Color must have exactly 2 commas \
			separating 3 RGB values\n");
		return (0);
	}
	return (1);
}

static int	parse_and_validate_rgb(char **rgb, t_rgb *color)
{
	int	i;

	color->r = -1;
	color->g = -1;
	color->b = -1;
	i = 0;
	while (i < 3)
	{
		if (!parse_rgb_component(rgb[i], i, color))
		{
			printf("Error: Invalid RGB component '%s'\
                - must be a number between 0-255\n", rgb[i]);
			free_split(rgb);
			return (0);
		}
		i++;
	}
	free_split(rgb);
	if (!validate_rgb_components(color))
	{
		printf("Error: RGB values must be between 0 and 255\n");
		return (0);
	}
	return (1);
}

int	parse_color(char *color_str, t_rgb *color)
{
	char	**rgb;
	int		component_count;

	if (!validate_color_format(color_str))
		return (0);
	rgb = ft_split(color_str, ',');
	if (!rgb)
	{
		printf("Error: Invalid color format\n");
		return (0);
	}
	component_count = count_components(rgb);
	if (component_count != 3)
	{
		printf("Error: Color must have exactly 3 RGB values (found %d)\n",
			component_count);
		free_split(rgb);
		return (0);
	}
	return (parse_and_validate_rgb(rgb, color));
}
