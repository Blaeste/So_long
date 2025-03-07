/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:20:24 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/04 13:12:28 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

//	Include
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

//	Define
# define WIDTH 256
# define HEIGHT 256

typedef struct s_map
{
	int		infile;
	int		line_count;
	char	**pattern;
	int		map_w;
	int		map_h;
	int		empty_tile;
	int		wall_tile;
	int		col_tile;
	int		end_tile;
	int		char_tile;
}	t_map;

typedef struct s_tex
{
	mlx_image_t	*w;
	mlx_image_t	*f;
	mlx_image_t	*p;
	mlx_image_t	*e;
	mlx_image_t	*c;
}	t_tex;

typedef struct s_pe
{
	int	p_x;
	int	p_y;
	int	n_x;
	int	n_y;
}	t_pe;

typedef struct s_data
{
	int				total_mov;
	int				anim_fram;
	mlx_t			*mlx;
	struct s_map	map;
	struct s_pe		pe;
	struct s_tex	tex;
}	t_data;

//	Prototype
void	ft_init(t_data *data);
void	ft_open(char *filename, t_data *data);
void	ft_read_map(t_data *data, char *filename);
int		ft_check_map(t_data *data);

// utils
int		ft_map_error(char *msg);
void	error_handler(char *msg, t_data *data, char *to_free);

// flood fill
int		ft_check_map_path(t_data *data);

// mlx
void	ft_init_mlx(t_data *d);
void	ft_draw_map(t_data *d);
void	ft_init_player(t_data *data);
void	ft_handle_input(mlx_key_data_t keydata, void *param);
void	ft_move_player(t_data *data, int dx, int dy);
void	ft_tex_to_img(mlx_image_t **img, t_data *d, char type);
void	ft_terminate(t_data *d, int win);
void	ft_close_window(void *param);

#endif //	SO_LONG_H