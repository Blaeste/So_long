/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:07:15 by eschwart          #+#    #+#             */
/*   Updated: 2025/03/04 14:03:08 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_map_error(char *msg)
{
	ft_dprintf(2, "Error\n%s\n", msg);
	return (1);
}

void	error_handler(char *msg, t_data *data, char *to_free)
{
	if (msg)
		perror(msg);
	if (to_free)
		free(to_free);
	if (data)
	{
		if (data->map.pattern)
		{
			ft_free_tab(data->map.pattern);
			data->map.pattern = NULL;
		}
		if (data->map.infile >= 0)
		{
			close(data->map.infile);
			data->map.infile = -1;
		}
		if (data->mlx != NULL)
			ft_terminate(data, 0);
	}
	exit(EXIT_FAILURE);
}

void	ft_open(char *filename, t_data *data)
{
	char	*full_path;

	full_path = malloc(sizeof(char) * (ft_strlen(filename) + 6));
	if (!full_path)
		error_handler("Error: ft_open malloc | utils.c", data, 0);
	ft_strlcpy(full_path, "map/", 6);
	ft_strlcat(full_path, filename, ft_strlen(filename) + 6);
	data->map.infile = open(full_path, O_RDONLY);
	if (data->map.infile < 0)
		error_handler("Error: ft_open infile | utils.c", data, full_path);
	free(full_path);
}

static void	ft_store_map(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(data->map.infile);
	while (line)
	{
		data->map.pattern[i++] = line;
		line = get_next_line(data->map.infile);
	}
	data->map.pattern[i] = NULL;
}

void	ft_read_map(t_data *data, char *filename)
{
	char	*line;

	line = get_next_line(data->map.infile);
	while (line)
	{
		free(line);
		data->map.line_count++;
		line = get_next_line(data->map.infile);
	}
	if (data->map.line_count == 0)
		error_handler("Error: map file is empty | utils.c", data, 0);
	data->map.pattern = malloc((data->map.line_count + 1) * sizeof(char *));
	if (!data->map.pattern)
		error_handler("Error: ft_read_map malloc |utils.c", data, 0);
	close(data->map.infile);
	data->map.infile = -1;
	ft_open(filename, data);
	if (data->map.infile < 0)
		error_handler("Error: reopening map ft_read_map | utils.c", data, 0);
	ft_store_map(data);
	close(data->map.infile);
	data->map.infile = -1;
}
