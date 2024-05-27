/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:28 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 05:31:01 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_wall_check(t_data *data)
{
	if (!data->e_pressed)
		ft_close_all_doors(data);
	if (data->e_pressed && data->ray->wall == 2
		&& data->ray->perpwalldist < 1)
	{
		ft_open_closest_door_by_player(data);
		ft_wallhit(data);
		ft_raydist(data);
	}	
}

void	ft_wall_check1(t_data *data)
{
	if (data->e_pressed && data->ray->wall == 2
		&& data->ray->perpwalldist < 1)
	{
		ft_wallhit(data);
		ft_raydist(data);
	}
}
