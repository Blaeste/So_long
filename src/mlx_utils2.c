/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:01:11 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/04 13:56:22 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_close_window(void *param)
{
	ft_terminate((t_data *)param, 0);
}

void	ft_tex_to_img(mlx_image_t **img, t_data *d, char type)
{
	mlx_texture_t	*tmp;

	if (type == 'w')
		tmp = mlx_load_png("textures/1.png");
	else if (type == 'f')
		tmp = mlx_load_png("textures/0.png");
	else if (type == 'p')
		tmp = mlx_load_png("textures/P.png");
	else if (type == 'e')
		tmp = mlx_load_png("textures/E.png");
	else if (type == 'c')
		tmp = mlx_load_png("textures/C.png");
	if (!tmp)
		error_handler("Error:\n Failed to load texture.\n", d, NULL);
	*img = mlx_texture_to_image(d->mlx, tmp);
	mlx_delete_texture(tmp);
}

void	ft_terminate(t_data *d, int win)
{
	if (!d)
		return ;
	if (d->mlx != NULL)
	{
		mlx_close_window(d->mlx);
		if (d->tex.w)
			mlx_delete_image(d->mlx, d->tex.w);
		if (d->tex.f)
			mlx_delete_image(d->mlx, d->tex.f);
		if (d->tex.p)
			mlx_delete_image(d->mlx, d->tex.p);
		if (d->tex.e)
			mlx_delete_image(d->mlx, d->tex.e);
		if (d->tex.c)
			mlx_delete_image(d->mlx, d->tex.c);
		mlx_terminate(d->mlx);
	}
	if (d->map.pattern != NULL)
		ft_free_tab(d->map.pattern);
	if (d->map.infile > 0)
		close(d->map.infile);
	if (win == 1)
		ft_printf("🎉 Tu as gagné !\n");
	exit(EXIT_SUCCESS);
}
