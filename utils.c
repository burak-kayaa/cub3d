/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 02:08:35 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_fill_pixel(t_data *data, int x, int y, char type)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (type == '1')
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x00FFFFFF;
			else if (type == '0')
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x00000000;
			j++;
		}
		i++;
	}
}

void	store_ray(t_data *data, int x, int y, int x2, int y2, int i)
{	
	data->ray->log[i] = (int *)malloc(sizeof(int) * 4);
	data->ray->log[i][0] = x;
	data->ray->log[i][1] = y;
	data->ray->log[i][2] = x2;
	data->ray->log[i][3] = y2;
}

double	ft_ray_length(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	ft_fill_floor_and_ceiling(t_data *data)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (i < 1080 / 2)
	{
		n = 0;
		while (n < 1920)
		{
			data->mlx_o_data[i * 1920 + n] = 0x00575757;
			n++;
		}
		i++;
	}
	while (i < 1080)
	{
		n = 0;
		while (n < 1920)
		{
			data->mlx_o_data[i * 1920 + n] = 0x005b95b0;
			n++;
		}
		i++;
	}
}

