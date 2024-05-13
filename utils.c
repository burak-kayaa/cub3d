/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/13 22:34:37 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_fill_pixel(t_data *data, int x, int y, char type)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i, y + j, 0x737373);
			else
			{
				if (type == '1')
					mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i, y + j, 0x00FFFFFF);
				else if (type == '0')
					mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + i, y + j, 0x00000000);
			}
			j++;
		}
		i++;
	}
}

void	store_ray(t_data *data, int x, int y, int x2, int y2, int i)
{	
	data->ray->log[i] = (int *)malloc(sizeof(int) * 4);
	data->ray->log[i][0] = x;
	data->ray->log[i][1] = y;
	data->ray->log[i][2] = x2;
	data->ray->log[i][3] = y2;
}

void	ft_mlx_print_line(t_data *data, int x, int y, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		px;
	int		py;

	px = data->pos_x;
	py = data->pos_y;
	dx = abs(x2 - x);
	sx = x < x2 ? 1 : -1;
	dy = -abs(y2 - y);
	sy = y < y2 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		int m = (int)px / TILE_SIZE;
		int n = (int)py / TILE_SIZE;
		if (data->map->map[n][m] == '1')
			break ;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		if (x == x2 && y == y2)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx * 12;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy * 12;
		}
		px = x;
		py = y;
	}
}