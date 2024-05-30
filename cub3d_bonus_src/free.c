/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:23:49 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/30 19:03:07 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_map(t_map *map)
{
	if (map->floor)
		ft_free_array(map->floor);
	if (map->ceiling)
		ft_free_array(map->ceiling);
	if (map->map)
		ft_free_array(map->map);
	if (map->flood_fill)
		ft_free_array(map->flood_fill);
	if (map->ceiling_str)
		free(map->ceiling_str);
	if (map->floor_str)
		free(map->floor_str);
	if (map->map_str)
		free(map->map_str);
	if (map->wall_textures)
		ft_free_array(map->wall_textures);
	free(map);
}

void	free_doors(t_data *data)
{
	t_door	*door;
	int		i;

	i = 0;
	if (data->doors)
	{
		door = data->doors[i];
		while (door)
		{
			free(door);
			i++;
			door = data->doors[i];
		}
		free(data->doors);
	}
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
		ft_free_map(data->map);
	if (data->ray)
		free(data->ray);
	if (data->images)
	{
		while (++i < TOTAL_TEXTURES)
		{
			if (data->images[i])
			{
				if (data->images[i]->img)
					mlx_destroy_image(data->mlx_ptr, data->images[i]->img);
				free(data->images[i]);
			}
		}
		free(data->images[0]);
		free(data->images);
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_doors(data);
	free(data);
}

void	ft_error(char *str, t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	if (data)
		ft_free_data(data);
	data = NULL;
	exit(0);
}
