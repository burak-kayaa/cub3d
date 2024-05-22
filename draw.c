/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:08:21 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 01:37:11 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_wallhit(t_data *data)
{
	if (data->map->map[data->ray->map_x][data->ray->map_y] == '1' ||
		data->map->map[data->ray->map_x][data->ray->map_y] == '2' 
		
	)
	{
		if (data->map->map[data->ray->map_x][data->ray->map_y] == '2')
		{
			if (!data->is_door_open)
				data->ray->wall = 2;
			else
				data->ray->wall = 3;
		}
		else if (data->map->map[data->ray->map_x][data->ray->map_y] == 'U')
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

int	ft_check_sphit(t_data *data)
{
	if (data->ray->map_x >= data->map->map_x || data->ray->map_y >= data->map->map_y || data->ray->map_x <= 0 || data->ray->map_y <= 0 || data->map->map[data->ray->map_x][data->ray->map_y] == '1' || data->map->map[data->ray->map_x][data->ray->map_y] == '2')
		return (1);
	
	if (data->map->map[data->ray->map_x][data->ray->map_y] == 'U'
	)
	{
		data->ray->wall = 4;
	}
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

void	ft_raydist(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perpwalldist = data->ray->sidedistx - data->ray->deltadistx;
	else
		data->ray->perpwalldist = data->ray->sidedisty - data->ray->deltadisty;
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
