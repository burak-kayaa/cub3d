/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:36 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 06:40:57 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_wallhit(t_data *data)
{
	if (data->map->map[data->ray->map_x][data->ray->map_y] == WALL_CHAR ||
		data->map->map[data->ray->map_x][data->ray->map_y] == DOOR_CHAR)
	{
		if (data->map->map[data->ray->map_x][data->ray->map_y] == DOOR_CHAR)
			data->ray->wall = 2;
		else if (data->map->map[data->ray->map_x][data->ray->map_y] == SPRITE_CHAR)
			data->ray->wall = 4;
		else
			data->ray->wall = 1;
	}
}

void	ft_wallhit(t_data *data)
{
	data->ray->wall = 0;
	while (!data->ray->wall)
	{
		if (data->ray->sidedistx < data->ray->sidedisty)
		{
			data->ray->sidedistx += data->ray->deltadistx;
			data->ray->map_x += data->ray->stepx;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sidedisty += data->ray->deltadisty;
			data->ray->map_y += data->ray->stepy;
			data->ray->side = 1;
		}
		ft_check_wallhit(data);
	}
}

void	ft_raydist(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perpwalldist = data->ray->sidedistx - data->ray->deltadistx;
	else
		data->ray->perpwalldist = data->ray->sidedisty - data->ray->deltadisty;
	if (data->ray->perpwalldist < 0.001)
		data->ray->perpwalldist += 0.001;
	data->ray->lineheight = (int)(SCREENHEIGHT / data->ray->perpwalldist * 2);
	data->ray->drawstart = -data->ray->lineheight / 2 + SCREENHEIGHT / 2;
	if (data->ray->drawstart < 0)
		data->ray->drawstart = 0;
	data->ray->drawend = data->ray->lineheight / 2 + SCREENHEIGHT / 2;
	if (data->ray->drawend >= SCREENHEIGHT)
		data->ray->drawend = SCREENHEIGHT - 1;
}

void	ft_send_ray(t_data *data, int x)
{
	ft_direction(data);
	ft_wallhit(data);
	ft_raydist(data);
	ft_wall_check(data);
	ft_wall_check1(data);
	ft_texture(data, x, 0);
}
