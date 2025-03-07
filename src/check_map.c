/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:52:06 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/27 15:05:42 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	ft_input_map(t_data *data)
{
	int		i;
	int		j;
	char	**patt;

	patt = data->map.pattern;
	i = -1;
	while (patt[++i])
	{
		j = 0;
		while (patt[i][j])
		{
			if (patt[i][j] != '1' && patt[i][j] != '0' && patt[i][j] != 'P' &&
				patt[i][j] != 'E' && patt[i][j] != 'C' && patt[i][j] != '\n')
				return (ft_map_error("Invalid input take : 1 0 P E C"));
			j++;
		}
	}
	return (0);
}

static int	ft_check_map_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.map_w)
	{
		if (data->map.pattern[0][i] != '1' ||
			data->map.pattern[data->map.map_h - 1][i] != '1')
			return (ft_map_error("Map is not surrounded by walls"));
		i++;
	}
	i = 0;
	while (i < data->map.map_h)
	{
		if (data->map.pattern[i][0] != '1' ||
			data->map.pattern[i][data->map.map_w - 1] != '1')
			return (ft_map_error("Map is not surrounded by walls"));
		i++;
	}
	return (0);
}

static int	ft_check_map_rect(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.pattern[i])
	{
		if ((int)ft_strlen(data->map.pattern[i]) != data->map.map_w)
			return (ft_map_error("Map is not rectangular"));
		i++;
	}
	return (0);
}

static int	ft_check_map_elem(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.pattern[++i])
	{
		j = -1;
		while (data->map.pattern[i][++j])
		{
			if (data->map.pattern[i][j] == 'P')
				data->map.char_tile++;
			else if (data->map.pattern[i][j] == 'E')
				data->map.end_tile++;
			else if (data->map.pattern[i][j] == 'C')
				data->map.col_tile++;
		}
	}
	if (data->map.char_tile != 1)
		return (ft_map_error("Invalid number of player positions (P)"));
	if (data->map.end_tile != 1)
		return (ft_map_error("Invalid number of exits (E)"));
	if (data->map.col_tile < 1)
		return (ft_map_error("No collectibles (C) found"));
	return (0);
}

int	ft_check_map(t_data *data)
{
	if (!data->map.pattern || !data->map.pattern[0])
		return (ft_map_error("Map is NULL or empty"));
	while (data->map.pattern[data->map.map_h])
		data->map.map_h++;
	data->map.map_w = ft_strlen(data->map.pattern[0]);
	if (ft_input_map(data))
		return (1);
	if (ft_check_map_rect(data))
		return (1);
	if (data->map.pattern[0][data->map.map_w - 1] == '\n')
		data->map.map_w--;
	if (ft_check_map_walls(data))
		return (1);
	if (ft_check_map_elem(data))
		return (1);
	if (ft_check_map_path(data))
		return (1);
	return (0);
}
