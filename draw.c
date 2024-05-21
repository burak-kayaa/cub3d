/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:08:21 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 01:36:31 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_direction(t_data *data)
{
	if (data->ray->raydirx < 0)
	{
		data->ray->stepx = -1;
		data->ray->sidedistx = (data->ray->posx - data->ray->mapx)
			* data->ray->deltadistx;
	}
	else
	{
		data->ray->stepx = 1;
		data->ray->sidedistx = (data->ray->mapx + 1.0 - data->ray->posx)
			* data->ray->deltadistx;
	}
	if (data->ray->raydiry < 0)
	{
		data->ray->stepy = -1;
		data->ray->sidedisty = (data->ray->posy - data->ray->mapy)
			* data->ray->deltadisty;
	}
	else
	{
		data->ray->stepy = 1;
		data->ray->sidedisty = (data->ray->mapy + 1.0 - data->ray->posy)
			* data->ray->deltadisty;
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
			data->ray->mapx += data->ray->stepx;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sidedisty += data->ray->deltadisty;
			data->ray->mapy += data->ray->stepy;
			data->ray->side = 1;
		}
		if (data->map->map[data->ray->mapx][data->ray->mapy] == '1' || data->map->map[data->ray->mapx][data->ray->mapy] == '2')
		{
			if (data->map->map[data->ray->mapx][data->ray->mapy] == '2')
			{
				if (!data->is_door_open)
					data->ray->wall = 2;
				else
					data->ray->wall = 3;
			}
			else
				data->ray->wall = 1;
		}
	}
}

void	ft_raydist(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perpwalldist = data->ray->sidedistx - data->ray->deltadistx;
	else
		data->ray->perpwalldist = data->ray->sidedisty - data->ray->deltadisty;
	data->ray->lineheight = (int)(1080 / data->ray->perpwalldist * 2);
	data->ray->drawstart = -data->ray->lineheight / 2 + 1080 / 2;
	if (data->ray->drawstart < 0)
		data->ray->drawstart = 0;
	data->ray->drawend = data->ray->lineheight / 2 + 1080 / 2;
	if (data->ray->drawend >= 1080)
		data->ray->drawend = 1080 - 1;
}

void	ft_send_ray(t_data *data, int x)
{
	ft_direction(data);
	ft_wallhit(data);
	ft_raydist(data);
	
	// eğer oyuncu zaten kapıdan uzaktaysa direkt kapıyı kapat
	if (data->ray->perpwalldist >= 1.5 && data->map->map[(int)data->ray->posx][(int)data->ray->posy] != '2')
		data->is_door_open = 0;

	if (data->ray->wall == 3 && data->ray->perpwalldist < 1.5 && !data->e_pressed)
	{
		data->ray->wall = 0;
		data->is_door_open = 0;
		ft_wallhit(data);
		ft_raydist(data);
	}
	if (data->e_pressed && data->ray->wall == 2 && data->ray->perpwalldist < 1.5)
	{
		data->ray->wall = 0;
		data->is_door_open = 1;
		ft_wallhit(data);
		ft_raydist(data);
	}
	if (data->e_pressed && data->ray->wall == 3 && data->ray->perpwalldist < 1.5)
	{
		ft_wallhit(data);
		ft_raydist(data);
	}

	if (data->e_pressed && data->ray->wall == 2 && data->ray->perpwalldist < 1.5)
	{
		data->ray->wall = 0;
		ft_wallhit(data);
		ft_raydist(data);
		data->is_door_open = 1;
	}
	


	// printf("data->is_door_open: %d\n", data->is_door_open);
	ft_texture(data, x);
}

void	ft_log_ray(t_data *data, int x)
{
	data->ray->log[x][0] = data->ray->mapx;
	data->ray->log[x][1] = data->ray->mapy;
	data->ray->log[x][2] = data->ray->mapx + data->ray->raydirx * 100;
	data->ray->log[x][3] = data->ray->mapy + data->ray->raydiry * 100;
}

void	ft_ray_casting(t_data *data)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		data->ray->camerax = 2 * x / (double)SCREENWIDTH - 1;
		data->ray->raydirx = data->ray->dirx + data->ray->planex
			* data->ray->camerax;
		data->ray->raydiry = data->ray->diry + data->ray->planey
			* data->ray->camerax;
		data->ray->mapx = (int)data->ray->posx;
		data->ray->mapy = (int)data->ray->posy;
		data->ray->deltadistx = fabs(1 / data->ray->raydirx);
		data->ray->deltadisty = fabs(1 / data->ray->raydiry);
		// ft_log_ray(data, x);
		ft_send_ray(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img, 0, 0);
}
