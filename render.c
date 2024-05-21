/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:58 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 02:04:21 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_fill_pixel(t_data *data, int x, int y, char type)
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
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x80FFFFFF;
			else if (type == '2')
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x8000FF00;
			else
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x80000000;
			j++;
		}
		i++;
	}
}

void ft_draw_player_angle(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	int angle;

	i = 0;
	// find the angle based on the player's direction data->ray->dirx and data->ray->diry. use PI
	angle = atan2(data->ray->diry, data->ray->dirx) * 180 / M_PI;
	printf("angle: %d\n", angle);
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (angle == 0)
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = color;
			else if (angle == 90)
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = color;
			else if (angle == 180)
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = color;
			else if (angle == 270)
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = color;
			j++;
		}
		i++;
	}
}

void	ft_render_map(t_data *data, int render_fc)
{
	int	i;
	int	j;

	if (render_fc)
		ft_fill_floor_and_ceiling(data);
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, \
				data->map->map[i][j]);
			j++;
		}
		i++;
	}
	ft_draw_square_on_coords(data, data->ray->posy * TILE_SIZE,
		data->ray->posx * TILE_SIZE, 0x00FDF0000);
	// ft_draw_player_angle(data, data->ray->posy * TILE_SIZE,
	// 	data->ray->posx * TILE_SIZE, 0x00FDF0000);
}
