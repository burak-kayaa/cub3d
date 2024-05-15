/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:58 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 01:14:00 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_render_map(t_data *data)
{
	int	i;
	int	j;
	int	k;

	// fill the board with black
	ft_fill_floor_and_ceiling(data);
	
	k = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			ft_fill_pixel(data, j * TILE_SIZE, i * TILE_SIZE, data->map->map[i][j]);
			j++;
		}
		i++;
	}
}
