/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:28 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:57:31 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_wall_check(t_data *data)
{
	if (data->ray->perpwalldist >= 1.5
		&& data->map->map[(int)data->ray->posx][(int)data->ray->posy] != '2')
		data->is_door_open = 0;
	if (data->ray->wall == 3 && data->ray->perpwalldist < 1.5
		&& !data->e_pressed)
	{
		data->ray->wall = 0;
		data->is_door_open = 0;
		ft_wallhit(data);
		ft_raydist(data);
	}
	if (data->e_pressed && data->ray->wall == 2
		&& data->ray->perpwalldist < 1.5)
	{
		data->ray->wall = 0;
		data->is_door_open = 1;
		ft_wallhit(data);
		ft_raydist(data);
	}
}

void	ft_wall_check1(t_data *data)
{
	if (data->e_pressed && data->ray->wall == 3
		&& data->ray->perpwalldist < 1.5)
	{
		ft_wallhit(data);
		ft_raydist(data);
	}
	if (data->e_pressed && data->ray->wall == 2
		&& data->ray->perpwalldist < 1.5)
	{
		data->ray->wall = 0;
		ft_wallhit(data);
		ft_raydist(data);
		data->is_door_open = 1;
	}
}
