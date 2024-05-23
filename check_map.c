/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 21:49:49 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(data->map->map);
	exit(0);
}

int	player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	check_player_amount(t_data *data)
{
	int	i;
	int	j;
	int	player_amount;

	i = 0;
	player_amount = 0;
	while (i < data->map->map_y && data->map->map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (player(data->map->map[i][j]))
				player_amount++;
			j++;
		}
		i++;
	}
	if (player_amount != 1)
		ft_error("Player amount is not correct", data);
}

void	check_map_characters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->map_y && data->map->map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (data->map->map[i][j] != '0' && data->map->map[i][j] != '1'
				&& data->map->map[i][j] != '2' && data->map->map[i][j] != 'N'
				&& data->map->map[i][j] != 'S' && data->map->map[i][j] != 'W'
				&& data->map->map[i][j] != 'E' && data->map->map[i][j] != ' '
				&& data->map->map[i][j] != 'U')
				ft_error("Map characters are not correct", data);
			j++;
		}
		i++;
	}
}

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_putstr_fd(map[i], 2);
		ft_putchar_fd('\n', 2);
		i++;
	}
}

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
			if (player(data->map->flood_fill[i][j]) || data->map->flood_fill[i][j] == '0' || data->map->flood_fill[i][j] == '1')
			{
				ft_print_map(data->map->flood_fill);
				printf("data->map->flood_fill[%d][%d]: %c\n", i, j, data->map->flood_fill[i][j]);
				ft_error("hata", data);
				exit(0);
			}
			j++;	
		}
		i++;
	}
}

void flood_fill(t_data *data, int y, int x)
{
	if (y < 0 || x < 0 || y >= data->map->map_y || x >= (int)ft_strlen(data->map->map[y]) || data->map->flood_fill[y][x] == 'F')
		return;
	if (data->map->flood_fill[y][x] == '0' || data->map->flood_fill[y][x] == 'U' || data->map->flood_fill[y][x] == '2' || data->map->flood_fill[y][x] == 'N' || data->map->flood_fill[y][x] == 'S' || data->map->flood_fill[y][x] == 'W' || data->map->flood_fill[y][x] == 'E' || data->map->flood_fill[y][x] == '1')
	{
		data->map->flood_fill[y][x] = 'F';
		flood_fill(data, y + 1, x);
		flood_fill(data, y - 1, x);
		flood_fill(data, y, x + 1);
		flood_fill(data, y, x - 1);
	}
}

void	ft_check_stars(t_data *data)
{
	int i;
	int j;
	char *line;

	i = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		line = data->map->map[i];
		while (j < (int)ft_strlen(line))
		{
			if (line[j] == '*')
			{
				if (j > 0 && !(line[j - 1] == '*' || line[j - 1] == '1'))
					ft_error("Map is not closed from left", data);
				if (j < (int)ft_strlen(line) - 1 && !(line[j + 1] == '*' || line[j + 1] == '1'))
					ft_error("Map is not closed from right", data);
				if (i > 0 && !(data->map->map[i - 1][j] == '*' || data->map->map[i - 1][j] == '1'))
					ft_error("Map is not closed from up", data);
				if (i < data->map->map_y - 1 && !(data->map->map[i + 1][j] == '*' || data->map->map[i + 1][j] == '1'))
					ft_error("Map is not closed from down", data);
			}
			j++;
		}
		i++;
	}
}

void ft_check_border(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (i == 0 || i == data->map->map_y - 1 || j == 0 || j == (int)ft_strlen(data->map->map[i]) - 1)
			{
				if (data->map->map[i][j] != '1' && data->map->map[i][j] != '*')
					ft_error("Map is not closed from border", data);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_map(t_data *data)
{
	flood_fill(data, (int)data->ray->posy, (int)data->ray->posx);
	check_flood(data);
	check_player_amount(data);
	check_map_characters(data);
	char **mapp = malloc(sizeof(char *) * (data->map->map_y + 1));
	int i = 0;
	int j = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		mapp[i] = ft_calloc(sizeof(char), (data->map->map_x + 1));
		ft_memset(mapp[i], '*', data->map->map_x);
		ft_memcpy(mapp[i], data->map->map[i], ft_strlen(data->map->map[i]));
		while (j < (int)data->map->map_x)
		{
			if (mapp[i][j] == ' ')
				mapp[i][j] = '*';
			j++;	 
		}
		i++;
	}
	mapp[i] = NULL;
	data->map->map = mapp;
	ft_check_stars(data);
	ft_check_border(data);
}