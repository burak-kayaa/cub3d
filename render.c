/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:58 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 22:55:34 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_pixel(t_data *data, int x, int y, char type)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (type == '1')
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x80FFFFFF;
			else if (type == '2')
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x8000FF00;
			else if (type == '*')
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x80FF0000;
			else if (type == 'P')
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x800000FF;
			else
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x80000000;
			j++;
		}
		i++;
	}
}

void	ft_render_map(t_data *data, int render_fc)
{
    int	i;
    int	j;
	int	user_x;
	int	user_y;

	i = 0;
	if (render_fc)
		ft_fill_floor_and_ceiling(data);
	user_x = (int)data->ray->posy;
	user_y = (int)data->ray->posx;
	while (i < MINIMAPHEIGHT)
	{
		j = 0;
		while (j < MINIMAPWIDTH)
		{
			if (user_x - (MINIMAPHEIGHT / 2) + j < 0 || user_y - (MINIMAPHEIGHT / 2) + i < 0 || user_x - (MINIMAPHEIGHT / 2) + j >= data->map->map_x || user_y - (MINIMAPHEIGHT / 2) + i >= data->map->map_y)
				ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, '*');
			else if (data->map->map[user_y - (MINIMAPHEIGHT / 2) + i][user_x - (MINIMAPHEIGHT / 2) + j] == '1')
				ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, '1');
			else if (data->map->map[user_y - (MINIMAPHEIGHT / 2) + i][user_x - (MINIMAPHEIGHT / 2) + j] == '2')
				ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, '2');
			else
				ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, '0');
			j++;
		}
		i++;
	}
	ft_fill_pixel(data, (MINIMAPWIDTH / 2) * TILE_SIZE, (MINIMAPHEIGHT / 2) * TILE_SIZE, 'P');
}
