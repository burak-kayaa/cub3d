/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:51:00 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 17:27:37 by burkaya          ###   ########.fr       */
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
			|| data->map->flood_fill[i][j] == '0' \
			|| data->map->flood_fill[i][j] == '1')
				ft_error("Multiple maps", data);
			j++;
		}
		i++;
	}
	ft_free_array(data->map->flood_fill);
}

void	flood_fill(t_data *data, int y, int x)
{
	if (y < 0 || x < 0 || y >= data->map->map_y \
	|| x >= (int)ft_strlen(data->map->map[y]) \
	|| data->map->flood_fill[y][x] == 'F')
		return ;
	if (data->map->flood_fill[y][x] == '0' \
	|| data->map->flood_fill[y][x] == 'U' \
	|| data->map->flood_fill[y][x] == '2' || data->map->flood_fill[y][x] == 'N' \
	|| data->map->flood_fill[y][x] == 'S' || data->map->flood_fill[y][x] == 'W' \
	|| data->map->flood_fill[y][x] == 'E' || data->map->flood_fill[y][x] == '1')
	{
		data->map->flood_fill[y][x] = 'F';
		flood_fill(data, y + 1, x);
		flood_fill(data, y - 1, x);
		flood_fill(data, y, x + 1);
		flood_fill(data, y, x - 1);
	}
}
