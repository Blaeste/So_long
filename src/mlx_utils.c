/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:25:53 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/07 10:41:38 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_handle_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_terminate(data, 0);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		ft_move_player(data, 0, -1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		ft_move_player(data, 0, 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		ft_move_player(data, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		ft_move_player(data, 1, 0);
}

static void	ft_render_tile(t_data *d, int x, int y)
{
	char	tile;

	tile = d->map.pattern[y][x];
	mlx_image_to_window(d->mlx, d->tex.f, x * 64, y * 64);
	if (tile == '1')
		mlx_image_to_window(d->mlx, d->tex.w, x * 64, y * 64);
	else if (tile == 'E')
		mlx_image_to_window(d->mlx, d->tex.e, x * 64, y * 64);
	else if (tile == 'C')
		mlx_image_to_window(d->mlx, d->tex.c, x * 64, y * 64);
	else if (tile == 'P')
		mlx_image_to_window(d->mlx, d->tex.p, x * 64, y * 64);
}

void	ft_move_player(t_data *d, int dx, int dy)
{
	char	*tile;

	d->pe.n_x = d->pe.p_x + dx;
	d->pe.n_y = d->pe.p_y + dy;
	tile = &d->map.pattern[d->pe.n_y][d->pe.n_x];
	if (*tile == '1')
		return ;
	if (*tile == 'C')
	{
		d->map.col_tile--;
		*tile = '0';
	}
	if (*tile == 'E' && d->map.col_tile == 0)
		ft_terminate(d, 1);
	if (d->map.pattern[d->pe.p_y][d->pe.p_x] == 'E')
		d->map.pattern[d->pe.p_y][d->pe.p_x] = 'E';
	else
		d->map.pattern[d->pe.p_y][d->pe.p_x] = '0';
	ft_render_tile(d, d->pe.p_x, d->pe.p_y);
	d->pe.p_x = d->pe.n_x;
	d->pe.p_y = d->pe.n_y;
	if (d->map.pattern[d->pe.p_y][d->pe.p_x] != 'E')
		d->map.pattern[d->pe.p_y][d->pe.p_x] = 'P';
	ft_render_tile(d, d->pe.p_x, d->pe.p_y);
	ft_printf("Total move: %i\n", ++d->total_mov);
}

void	ft_init_mlx(t_data *d)
{
	d->mlx = mlx_init(d->map.map_w * 64, d->map.map_h * 64, "so_long", true);
	if (!d->mlx)
		error_handler("Error: MLX initialization failed", d, NULL);
	ft_tex_to_img(&d->tex.w, d, 'w');
	ft_tex_to_img(&d->tex.f, d, 'f');
	ft_tex_to_img(&d->tex.p, d, 'p');
	ft_tex_to_img(&d->tex.e, d, 'e');
	ft_tex_to_img(&d->tex.c, d, 'c');
	if (!d->tex.w || !d->tex.f || !d->tex.p || !d->tex.e || !d->tex.c)
		error_handler("Error:\n Failed to load image", d, NULL);
}

void	ft_draw_map(t_data *d)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < d->map.map_h)
	{
		x = 0;
		while (x < d->map.map_w)
		{
			tile = d->map.pattern[y][x];
			mlx_image_to_window(d->mlx, d->tex.f, x * 64, y * 64);
			if (tile == '1')
				mlx_image_to_window(d->mlx, d->tex.w, x * 64, y * 64);
			else if (tile == 'E')
				mlx_image_to_window(d->mlx, d->tex.e, x * 64, y * 64);
			else if (tile == 'C')
				mlx_image_to_window(d->mlx, d->tex.c, x * 64, y * 64);
			x++;
		}
		y++;
	}
	mlx_image_to_window(d->mlx, d->tex.p, d->pe.p_x * 64, d->pe.p_y * 64);
}
