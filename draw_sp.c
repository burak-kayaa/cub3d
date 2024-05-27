/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:32 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 13:38:57 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_sphit(t_data *data)
{
	if (data->map->map[data->ray->map_x][data->ray->map_y] == WALL_CHAR
		|| (data->map->map[data->ray->map_x][data->ray->map_y] == DOOR_CHAR))
		return (1);
	if (data->map->map[data->ray->map_x][data->ray->map_y] == SPRITE_CHAR)
		data->ray->wall = 4;
	return (0);
}

int	ft_sphit(t_data *data)
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
		if (ft_check_sphit(data))
			return (1);
	}
	// data->ray->sidedistx = 3.34;
	// data->ray->sidedisty = 2.35;
	return (0);
}

void	ft_send_ray_for_sp(t_data *data, int x, int i)
{
	ft_direction(data);
	if (!ft_sphit(data))
	{
		ft_raydist(data);
		ft_wall_check(data);
		ft_wall_check1(data);
		ft_texture(data, x, i);
	}
}
