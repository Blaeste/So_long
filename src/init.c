/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:00:33 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/04 13:55:30 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_init(t_data *data)
{
	data->total_mov = 0;
	data->map.infile = -1;
	data->map.line_count = 0;
	data->map.pattern = NULL;
	data->map.map_w = 0;
	data->map.map_h = 0;
	data->map.empty_tile = 0;
	data->map.wall_tile = 0;
	data->map.col_tile = 0;
	data->map.end_tile = 0;
	data->map.char_tile = 0;
	data->tex.w = NULL;
	data->tex.f = NULL;
	data->tex.p = NULL;
	data->tex.e = NULL;
	data->tex.c = NULL;
	data->mlx = NULL;
}

void	ft_init_player(t_data *data)
{
	int	x;
	int	y;

	data->pe.p_x = -1;
	data->pe.p_y = -1;
	data->pe.n_x = -1;
	data->pe.n_y = -1;
	y = 0;
	while (y < data->map.map_h)
	{
		x = 0;
		while (data->map.pattern[y][x])
		{
			if (data->map.pattern[y][x] == 'P')
			{
				data->pe.p_x = x;
				data->pe.p_y = y;
			}
			x++;
		}
		y++;
	}
}
