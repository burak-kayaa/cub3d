/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:16 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 15:27:46 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_open_door_map(t_data *data, t_door *door, int x, int y)
{
	if (data->map->map[y][x] == DOOR_CHAR)
	{
		data->map->map[y][x] = FLOOR_CHAR;
		door->is_open = 1;
	}
}

void	ft_close_door_map(t_data *data, t_door *door, int x, int y)
{
	if (data->map->map[y][x] == FLOOR_CHAR)
	{
		data->map->map[y][x] = DOOR_CHAR;
		door->is_open = 0;
	}
}

int	ft_is_player_in_or_around_wall(t_data *data, t_door *door)
{
	int	player_x;
	int	player_y;

	player_x = (int)data->ray->posx;
	player_y = (int)data->ray->posy;
	if ((door->y + 1 == player_x && door->x == player_y)
		|| (door->y - 1 == player_x && door->x == player_y)
		|| (door->y == player_x && door->x + 1 == player_y)
		|| (door->y == player_x && door->x - 1 == player_y)
		|| (door->y + 1 == player_x && door->x + 1 == player_y)
		|| (door->y + 1 == player_x && door->x - 1 == player_y)
		|| (door->y - 1 == player_x && door->x + 1 == player_y)
		|| (door->y - 1 == player_x && door->x - 1 == player_y)
		|| (door->y == player_x && door->x == player_y))
		return (1);
	return (0);
}
