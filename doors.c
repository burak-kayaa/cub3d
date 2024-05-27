/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:28:44 by egumus            #+#    #+#             */
/*   Updated: 2024/05/27 15:27:43 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_doors_helper(t_data *data)
{
	int	count;
	int	y;
	int	x;

	y = -1;
	count = 0;
	while (++y < data->map->map_y)
	{
		x = -1;
		while (++x < (int)ft_strlen(data->map->map[y]))
		{
			if (data->map->map[y][x] == DOOR_CHAR)
			{
				data->doors[count] = malloc(sizeof(t_door));
				if (!data->doors[count])
					ft_error("Memory allocation error", data);
				data->doors[count]->x = x;
				data->doors[count]->y = y;
				data->doors[count]->is_open = 0;
				count++;
			}
		}
	}
	data->doors[count] = NULL;
}

void	ft_init_doors(t_data *data)
{
	int	x;
	int	y;
	int	count;

	y = -1;
	count = 0;
	while (++y < data->map->map_y)
	{
		x = -1;
		while (++x < (int)ft_strlen(data->map->map[y]))
		{
			if (data->map->map[y][x] == DOOR_CHAR)
				count++;
		}
	}
	data->doors = malloc(sizeof(t_door) * (count + 1));
	if (!data->doors)
		ft_error("Memory allocation error", data);
	ft_init_doors_helper(data);
}

void	ft_close_all_doors(t_data *data)
{
	t_door	*door;
	int		i;

	i = 0;
	if (data->doors == NULL)
		return ;
	door = data->doors[i];
	while (door)
	{
		if (door->y == (int)data->ray->posx && door->x == (int)data->ray->posy)
		{
			ft_open_door_map(data, door, door->x, door->y);
			door = data->doors[++i];
			continue ;
		}
		ft_close_door_map(data, door, door->x, door->y);
		door = data->doors[++i];
	}
}

int	ft_is_any_door_open(t_data *data)
{
	int		i;
	t_door	*door;

	i = 0;
	if (data->doors == NULL)
		return (-1);
	door = data->doors[i];
	while (door)
	{
		if (door->is_open)
			return (1);
		door = data->doors[++i];
	}
	return (0);
}

void	ft_open_closest_door_by_player(t_data *data)
{
	int		i;
	t_door	*door;

	if (data->doors == NULL)
		return ;
	i = 0;
	door = data->doors[i];
	if (ft_is_any_door_open(data) != 0)
		return ;
	while (door)
	{
		if (ft_is_player_in_or_around_wall(data, door))
		{
			if (data->doors[i]->is_open)
				ft_close_door_map(data, data->doors[i], \
					data->doors[i]->x, data->doors[i]->y);
			else
				ft_open_door_map(data, data->doors[i], \
					data->doors[i]->x, data->doors[i]->y);
			break ;
		}
		door = data->doors[++i];
	}
}
