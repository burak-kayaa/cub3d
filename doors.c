/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:28:44 by egumus            #+#    #+#             */
/*   Updated: 2024/05/27 05:45:49 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_open_door_map(t_data *data, t_door *door, int x, int y)
{
	if (data->map->map[y][x] == '2')
	{
		data->map->map[y][x] = '0';
		door->is_open = 1;
	}
}

void	ft_close_door_map(t_data *data, t_door *door, int x, int y)
{
	if (data->map->map[y][x] == '0')
	{
		data->map->map[y][x] = '2';
		door->is_open = 0;
	}
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
			if (data->map->map[y][x] == '2')
				count++;
		}
	}
	data->doors = malloc(sizeof(t_door) * (count + 1));
	if (!data->doors)
		ft_error("Memory allocation error", data);
	y = -1;
	count = 0;
	while (++y < data->map->map_y)
	{
		x = -1;
		while (++x < (int)ft_strlen(data->map->map[y]))
		{
			if (data->map->map[y][x] == '2')
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

void	ft_toggle_door(t_data *data, int door_index)
{
	if (data->doors[door_index]->is_open)
		ft_close_door_map(data, data->doors[door_index], data->doors[door_index]->x, data->doors[door_index]->y);
	else
		ft_open_door_map(data, data->doors[door_index], data->doors[door_index]->x, data->doors[door_index]->y);
}

t_door	*ft_get_door_by_location(t_data *data, int x, int y)
{
	int	i;

	i = -1;
	while (++i < data->map->map_y)
	{
		if (data->doors[i]->x == x && data->doors[i]->y == y)
			return (data->doors[i]);
	}
	return (NULL);
}

int	ft_get_door_index(t_data *data, t_door *door)
{
	int	i;

	i = -1;
	while (++i < data->map->map_y)
	{
		if (data->doors[i] == door)
			return (i);
	}
	return (-1);
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
		|| (door->y == player_x && door->x == player_y))
		return (1);
	return (0);
}

int	ft_is_any_door_open(t_data *data)
{
	int	i;
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
	t_door *door;

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
			printf("opening door for x: %d, y: %d\n", door->x, door->y);
			ft_toggle_door(data, i);
			break ;
		}
		door = data->doors[++i];
	}
}