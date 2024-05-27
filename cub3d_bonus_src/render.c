/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:16 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 18:44:44 by burkaya          ###   ########.fr       */
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
			if (type == WALL_CHAR)
				data->mlx_o_data[(y + j) * SCREENWIDTH + (x + i)] = 0x80FFFFFF;
			else if (type == DOOR_CHAR)
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

void	ft_render_map_helper(t_data *data, int i, int j)
{
	if (data->ray->user_x - (MINIMAPHEIGHT / 2) + j < 0
		|| data->ray->user_y - (MINIMAPHEIGHT / 2) + i < 0
		|| data->ray->user_x - (MINIMAPHEIGHT / 2) + j >= data->map->map_x
		|| data->ray->user_y - (MINIMAPHEIGHT / 2) + i >= data->map->map_y
		|| data->map->map[data->ray->user_y - (MINIMAPHEIGHT / 2) \
		+ i][data->ray->user_x - (MINIMAPHEIGHT / 2) + j] == '*'
	)
		ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, '*');
	else if (data->map->map[data->ray->user_y - (MINIMAPHEIGHT / 2) + i]
		[data->ray->user_x - (MINIMAPHEIGHT / 2) + j] == WALL_CHAR)
		ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, WALL_CHAR);
	else if (data->map->map[data->ray->user_y - (MINIMAPHEIGHT / 2) + i]
		[data->ray->user_x - (MINIMAPHEIGHT / 2) + j] == DOOR_CHAR)
		ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, DOOR_CHAR);
	else
		ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, FLOOR_CHAR);
}

void	ft_render_map(t_data *data, int render_fc)
{
	int	i;
	int	j;

	i = 0;
	if (render_fc)
		ft_fill_floor_and_ceiling(data);
	data->ray->user_x = (int)data->ray->posy;
	data->ray->user_y = (int)data->ray->posx;
	while (i < MINIMAPHEIGHT)
	{
		j = 0;
		while (j < MINIMAPWIDTH)
		{
			ft_render_map_helper(data, i, j);
			j++;
		}
		i++;
	}
	ft_fill_pixel(data, (MINIMAPWIDTH / 2) * TILE_SIZE, \
		(MINIMAPHEIGHT / 2) * TILE_SIZE, 'P');
}

void	ft_render_hand_helper(t_data *data, int color, int y, int x)
{
	int			move;
	static int	i = 0;

	move = 10;
	if ((color & 0x00FFFFFF) != 0)
	{
		if (data->a_pressed || data->d_pressed
			|| data->s_pressed || data->w_pressed)
		{
			if ((i / 500000) % 2 == 1)
				data->mlx_o_data[(y + SCREENHEIGHT - 329 + move)
					* (SCREENWIDTH) + \
					(x + (SCREENHEIGHT + 585))] = color;
			else
				data->mlx_o_data[(y + SCREENHEIGHT - 329 - move)
					* SCREENWIDTH + (x + (SCREENHEIGHT + 585))] = color;
			i++;
		}
		else
			data->mlx_o_data[(y + SCREENHEIGHT - 339)
				* SCREENWIDTH + (x + (SCREENHEIGHT + 585))] = color;
	}
}

void	ft_render_hand(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < 185)
	{
		y = 0;
		while (y < 339)
		{
			color = data->images[13]->addr[y * 185 + x];
			ft_render_hand_helper(data, color, y, x);
			y++;
		}
		x++;
	}
}
