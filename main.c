/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:10:46 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 00:52:53 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_direction(t_data *data, char c)
{
	if (c == 'N')
	{
		data->ray->dirx = -1;
		data->ray->diry = 0;
	}
	else if (c == 'S')
	{
		data->ray->dirx = 1;
		data->ray->diry = 0;
	}
	else if (c == 'W')
	{
		data->ray->dirx = 0;
		data->ray->diry = -1;
	}
	else if (c == 'E')
	{
		data->ray->dirx = 0;
		data->ray->diry = 1;
	}
}

void	ft_set_plane(t_data *data, char c)
{
	if (c == 'N')
	{
		data->ray->planex = 0;
		data->ray->planey = 0.66;
	}
	else if (c == 'S')
	{
		data->ray->planex = 0;
		data->ray->planey = -0.66;
	}
	else if (c == 'W')
	{
		data->ray->planex = -0.66;
		data->ray->planey = 0;
	}
	else if (c == 'E')
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
			if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S'
				|| data->map->map[i][j] == 'W' || data->map->map[i][j] == 'E')
			{
				data->ray->posx = j + 0.5;
				data->ray->posy = i + 0.5;
				ft_get_direction(data, data->map->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (printf("Error\n"), 0);
	data = malloc(sizeof(t_data));
	data->map_path = argv[1];
	if (ft_init(data))
		return (printf("Error\n"), 0);
	if (ft_check_input(data, argv))
		return (printf("Error\n"), 0);
	ft_create_map(data);
	// ft_check_map(data);
	if (!data->map->map)
		return (free(data->ray), free(data->map), free(data), 1);
	ft_get_player_location(data);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->ray->posx, \
		data->ray->posy, 0x00FF0000);
	mlx_mouse_move(data->win_ptr, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 3, 0, key_released, data);
	mlx_hook(data->win_ptr, 2, 0, key_pressed, data);
	mlx_hook(data->win_ptr, 17, 0, ft_exit, data);
	mlx_loop(data->mlx_ptr);
}
