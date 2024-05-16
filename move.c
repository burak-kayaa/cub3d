/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:09:47 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 14:17:46 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	mouse_hook(t_data *data)
{
	int	*x;
	int	*y;

	x = malloc(sizeof(int));
	y = malloc(sizeof(int));
	mlx_mouse_get_pos(data->win_ptr, x, y);
	if (*x > 1100)
		data->right_pressed = 1;
	else if (*x < 800)
		data->left_pressed = 1;
	else
	{
		data->right_pressed = 0;
		data->left_pressed = 0;
	}
	return (free(x), free(y), 0);
}

int	ft_player_check(t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->pos_x;
	new_y = data->pos_y;
	if (data->left_pressed)
	{
		data->angle -= 0.1;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		data->delta_x = cos(data->angle) * 2;
		data->delta_y = sin(data->angle) * 2;
	}
	if (data->right_pressed)
	{
		data->angle += 0.1;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		data->delta_x = cos(data->angle) * 2;
		data->delta_y = sin(data->angle) * 2;
	}
	if (data->w_pressed)
	{
		new_x += data->delta_x;
		new_y += data->delta_y;
	}
	if (data->s_pressed)
	{
		new_x -= data->delta_x;
		new_y -= data->delta_y;
	}
	if (data->a_pressed)
	{
		new_x += data->delta_y;
		new_y -= data->delta_x;
	}
	if (data->d_pressed)
	{
		new_x -= data->delta_y;
		new_y += data->delta_x;
	}
	mouse_hook(data);
	if (data->map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return (1);
	ft_draw_square_on_coords(data, data->pos_x, data->pos_y, 0x00000000);
	data->pos_x = new_x;
	data->pos_y = new_y;
	return (0);
}

int	ft_player_move(t_data *data)
{
	if (ft_player_check(data))
		return (1);
	ft_draw_square_on_coords(data, data->pos_x, data->pos_y, 0x0000FF00);
	return (0);
}
