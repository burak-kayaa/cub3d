/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:51:00 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 18:14:44 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_flood(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (player(data->map->flood_fill[i][j])
			|| data->map->flood_fill[i][j] == FLOOR_CHAR \
			|| data->map->flood_fill[i][j] == WALL_CHAR)
				ft_error("Multiple maps", data);
			j++;
		}
		i++;
	}
}

void	flood_fill(t_data *data, int x, int y)
{
	if (y < 0 || x < 0 || y >= data->map->map_y \
	|| x >= (int)ft_strlen(data->map->map[y]) \
	|| data->map->flood_fill[y][x] == 'F')
		return ;
	if (data->map->flood_fill[y][x] == FLOOR_CHAR \
	|| data->map->flood_fill[y][x] == NORTH_CHAR \
	|| data->map->flood_fill[y][x] == SOUTH_CHAR \
	|| data->map->flood_fill[y][x] == WEST_CHAR \
	|| data->map->flood_fill[y][x] == EAST_CHAR \
	|| data->map->flood_fill[y][x] == WALL_CHAR)
	{
		data->map->flood_fill[y][x] = 'F';
		flood_fill(data, x + 1, y);
		flood_fill(data, x - 1, y);
		flood_fill(data, x, y + 1);
		flood_fill(data, x, y - 1);
	}
}
