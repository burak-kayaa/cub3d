/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:58 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/20 17:17:23 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_fill_pixel(t_data *data, int x, int y, char type)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (type == '1')
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x80FFFFFF;
			else
				data->mlx_o_data[(y + j) * 1920 + (x + i)] = 0x80000000;
			j++;
		}
		i++;
	}
}

void	ft_render_map(t_data *data, int render_fc)
{
	int	i;
	int	j;

	if (render_fc)
		ft_fill_floor_and_ceiling(data);
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, \
				data->map->map[i][j]);
			j++;
		}
		i++;
	}
}
