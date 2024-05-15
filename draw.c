/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:08:21 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 02:54:32 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_draw_vertical_image(t_data *data, int x, int y, int n)
{
	double distance;
	double px;
	double py;
	double draw_start;
	double draw_end;
	int i;

	i = 0;
	px = x;
	py = y;
	distance = 12000 / ft_ray_length(data->pos_x, data->pos_y, px, py);
	draw_start = (1080 / 2) - (distance / 2) * 2;
	draw_end = (1080 / 2) + (distance / 2) * 2;
	while (draw_start < draw_end)
	{
		if ((int)draw_start * 1920 + n < 1920 * 1080 && (int)draw_start * 1920 + n > 0)
			data->mlx_o_data[(int)draw_start * 1920 + n] = data->images[1]->addr[(int)((i * 64) % 64) + 32];
		draw_start++;
		i++;
	}
}

void	ft_mlx_print_line(t_data *data, int x, int y, int x2, int y2, int n)
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
		if (data->map->map[(int)py / TILE_SIZE][(int)px / TILE_SIZE] == '1')
		{
			data->mlx_o_data[py * 1920 + px] = 0x00FF0000;
			store_ray(data, x, y, px, py, n);
			ft_draw_vertical_image(data, px, py, n);
			break ;
		}
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
		px = x;
		py = y;
	}
}