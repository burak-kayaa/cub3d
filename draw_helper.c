/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:20:49 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 12:20:52 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_casting_for_sp(t_data *data, int x, int i)
{
	while (x < SCREENWIDTH)
	{
		data->ray->camerax = 2 * x / (double)SCREENWIDTH - 1;
		data->ray->raydirx = data->ray->dirx + data->ray->planex
			* data->ray->camerax;
		data->ray->raydiry = data->ray->diry + data->ray->planey
			* data->ray->camerax;
		data->ray->map_x = (int)data->ray->posx;
		data->ray->map_y = (int)data->ray->posy;
		data->ray->deltadistx = fabs(1 / data->ray->raydirx);
		data->ray->deltadisty = fabs(1 / data->ray->raydiry);
		ft_send_ray_for_sp(data, x, (int)((i / 5) % 7) + 6);
		x++;
	}
}

void	ft_ray_casting(t_data *data)
{
	int			x;
	static int	i;

	i++;
	x = 0;
	while (x < SCREENWIDTH)
	{
		data->ray->camerax = 2 * x / (double)SCREENWIDTH - 1;
		data->ray->raydirx = data->ray->dirx + data->ray->planex
			* data->ray->camerax;
		data->ray->raydiry = data->ray->diry + data->ray->planey
			* data->ray->camerax;
		data->ray->map_x = (int)data->ray->posx;
		data->ray->map_y = (int)data->ray->posy;
		data->ray->deltadistx = fabs(1 / data->ray->raydirx);
		data->ray->deltadisty = fabs(1 / data->ray->raydiry);
		ft_send_ray(data, x);
		x++;
	}
	x = 0;
	ft_ray_casting_for_sp(data, x, i);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img, 0, 0);
}

void	ft_direction(t_data *data)
{
	if (data->ray->raydirx < 0)
	{
		data->ray->stepx = -1;
		data->ray->sidedistx = (data->ray->posx - data->ray->map_x)
			* data->ray->deltadistx;
	}
	else
	{
		data->ray->stepx = 1;
		data->ray->sidedistx = (data->ray->map_x + 1.0 - data->ray->posx)
			* data->ray->deltadistx;
	}
	if (data->ray->raydiry < 0)
	{
		data->ray->stepy = -1;
		data->ray->sidedisty = (data->ray->posy - data->ray->map_y)
			* data->ray->deltadisty;
	}
	else
	{
		data->ray->stepy = 1;
		data->ray->sidedisty = (data->ray->map_y + 1.0 - data->ray->posy)
			* data->ray->deltadisty;
	}
}
