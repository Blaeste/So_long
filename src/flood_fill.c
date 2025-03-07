/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:58:45 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/03 13:28:20 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static char	**ft_copy_map(t_data *data)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (data->map.map_h + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->map.map_h)
	{
		copy[i] = ft_strdup(data->map.pattern[i]);
		if (!copy[i])
		{
			ft_free_tab(copy);
			error_handler("Copy map flood_fill fail", data, NULL);
		}
		i++;
	}
	copy[data->map.map_h] = NULL;
	return (copy);
}

static void	ft_flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	ft_flood_fill(map, x + 1, y);
	ft_flood_fill(map, x - 1, y);
	ft_flood_fill(map, x, y + 1);
	ft_flood_fill(map, x, y - 1);
}

static int	ft_validate_path(char **map, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (ft_map_error("Invalid path: col or exit unreachable"));
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_map_path(t_data *data)
{
	char	**copy;
	int		x;
	int		y;

	copy = ft_copy_map(data);
	if (!copy)
		return (ft_map_error("Memory allocation failed for map copy"));
	y = 0;
	while (y < data->map.map_h)
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'P')
			{
				ft_flood_fill(copy, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	if (ft_validate_path(copy, data->map.map_h))
		return (ft_free_tab(copy), 1);
	return (ft_free_tab(copy), 0);
}
