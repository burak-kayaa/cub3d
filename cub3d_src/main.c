/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:10:46 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/30 18:48:16 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_direction(t_data *data, char c)
{
	if (c == NORTH_CHAR)
	{
		data->ray->dirx = -1;
		data->ray->diry = 0;
	}
	else if (c == SOUTH_CHAR)
	{
		data->ray->dirx = 1;
		data->ray->diry = 0;
	}
	else if (c == WEST_CHAR)
	{
		data->ray->dirx = 0;
		data->ray->diry = -1;
	}
	else if (c == EAST_CHAR)
	{
		data->ray->dirx = 0;
		data->ray->diry = 1;
	}
}

void	ft_set_plane(t_data *data, char c)
{
	if (c == NORTH_CHAR)
	{
		data->ray->planex = 0;
		data->ray->planey = 0.66;
	}
	else if (c == SOUTH_CHAR)
	{
		data->ray->planex = 0;
		data->ray->planey = -0.66;
	}
	else if (c == WEST_CHAR)
	{
		data->ray->planex = -0.66;
		data->ray->planey = 0;
	}
	else if (c == EAST_CHAR)
	{
		data->ray->planex = 0.66;
		data->ray->planey = 0;
	}
}

void	ft_get_direction(t_data *data, char c)
{
	ft_set_direction(data, c);
	ft_set_plane(data, c);
}

void	ft_get_player_location(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == NORTH_CHAR
			|| data->map->map[i][j] == SOUTH_CHAR
			|| data->map->map[i][j] == WEST_CHAR
			|| data->map->map[i][j] == EAST_CHAR)
			{
				data->ray->posx = i + 0.5;
				data->ray->posy = j + 0.5;
				ft_get_direction(data, data->map->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error("Player not found", data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (printf("Error\n"), 1);
	data = malloc(sizeof(t_data));
	data->map_path = argv[1];
	check_extension(data->map_path);
	if (ft_init(data))
		return (ft_error("Malloc", data), 1);
	ft_create_map(data);
	ft_get_player_location(data);
	ft_check_map(data);
	mlx_loop_hook(data->mlx_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 3, 0, key_released, data);
	mlx_hook(data->win_ptr, 2, 0, key_pressed, data);
	mlx_hook(data->win_ptr, 17, 0, ft_exit, data);
	mlx_loop(data->mlx_ptr);
	ft_free_data(data);
}
