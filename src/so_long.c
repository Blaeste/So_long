/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:15:34 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/04 13:14:40 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	ft_valide_ex(const char *filename)
{
	size_t		len;
	int			dot;
	char		*str;

	dot = 0;
	len = ft_strlen(filename);
	str = (char *)filename;
	if (filename[0] == ' ' || filename[len - 1] == ' ')
		return (0);
	while (*str)
	{
		if (*str == '.')
			dot++;
		str++;
	}
	if (dot != 1)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
		return (0);
	return (1);
}

int32_t	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || av[1][0] == '\0')
	{
		ft_dprintf(2, "Error:\nUsage: %s <map_file.ber>\n", av[0]);
		exit (EXIT_FAILURE);
	}
	if (!ft_valide_ex(av[1]))
	{
		ft_dprintf(2, "Error:\nThe map file must have a .ber extension\n");
		exit (EXIT_FAILURE);
	}
	ft_init(&data);
	ft_open(av[1], &data);
	ft_read_map(&data, av[1]);
	if (ft_check_map(&data))
		error_handler(NULL, &data, NULL);
	ft_init_player(&data);
	ft_init_mlx(&data);
	ft_draw_map(&data);
	mlx_key_hook(data.mlx, ft_handle_input, &data);
	mlx_close_hook(data.mlx, ft_close_window, &data);
	mlx_loop(data.mlx);
	ft_free_tab(data.map.pattern);
	return (0);
}
