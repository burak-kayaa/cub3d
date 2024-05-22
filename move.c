/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:1:47 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/20 19:57:43 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_left(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->ray->dirx;
	data->ray->dirx = data->ray->dirx * cos(0.15) - data->ray->diry
		* sin(0.15);
	data->ray->diry = old_dirx * sin(0.15) + data->ray->diry
		* cos(0.15);
	old_planex = data->ray->planex;
	data->ray->planex = data->ray->planex * cos(0.15) - data->ray->planey
		* sin(0.15);
	data->ray->planey = old_planex * sin(0.15) + data->ray->planey
		* cos(0.15);
}

void	key_right(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->ray->dirx;
	data->ray->dirx = data->ray->dirx * cos(-0.05) - data->ray->diry
		* sin(-0.05);
	data->ray->diry = old_dirx * sin(-0.05) + data->ray->diry
		* cos(-0.05);
	old_planex = data->ray->planex;
	data->ray->planex = data->ray->planex * cos(-0.05) - data->ray->planey
		* sin(-0.05);
	data->ray->planey = old_planex * sin(-0.05) + data->ray->planey
		* cos(-0.05);
}

void	ft_move(t_data *data)
{
	if (data->w_pressed)
		key_w(data);
	if (data->s_pressed)
		key_s(data);
	if (data->left_pressed)
		key_left(data);
	if (data->right_pressed)
		key_right(data);
	if (data->a_pressed)
		key_a(data);
	if (data->d_pressed)
		key_d(data);
}

int	ft_player_move(t_data *data)
{
	ft_move(data);
	ft_draw_square_on_coords(data, data->ray->posy * TILE_SIZE,
		data->ray->posx * TILE_SIZE, 0x00000000);
	return (0);
}

void	ft_draw_square_on_coords(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	center_x;
	int	center_y;

	center_x = x - PLAYER_SIZE / 2;
	center_y = y - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			data->mlx_o_data[(center_y + j) * 1920 + (center_x + i)] = color;
			j++;
		}
		i++;
	}
}
