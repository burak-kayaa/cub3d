/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:16:10 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 09:17:23 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_sphit(t_data *data)
{
	if (data->ray->map_x >= data->map->map_x
		|| data->ray->map_y >= data->map->map_y || data->ray->map_x <= 0
		|| data->ray->map_y <= 0
		|| data->map->map[data->ray->map_x][data->ray->map_y] == '1'
		|| data->map->map[data->ray->map_x][data->ray->map_y] == '2')
		return (1);
	if (data->map->map[data->ray->map_x][data->ray->map_y] == 'U')
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
