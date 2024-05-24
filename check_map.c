/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:54:01 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_stars_helper(t_data *data, int i, int j, char *line)
{
	if (j > 0 && !(line[j - 1] == '*' || line[j - 1] == '1'))
		ft_error("Map is not closed from left", data);
	if (j < (int)ft_strlen(line) - 1 && !(line[j + 1] == '*' \
		|| line[j + 1] == '1'))
		ft_error("Map is not closed from right", data);
	if (i > 0 && !(data->map->map[i - 1][j] == '*' \
		|| data->map->map[i - 1][j] == '1'))
		ft_error("Map is not closed from up", data);
	if (i < data->map->map_y - 1
		&& !(data->map->map[i + 1][j] == '*' \
		|| data->map->map[i + 1][j] == '1'))
		ft_error("Map is not closed from down", data);
}

void	ft_check_stars(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		line = data->map->map[i];
		while (j < (int)ft_strlen(line))
		{
			if (line[j] == '*')
				ft_check_stars_helper(data, i, j, line);
			j++;
		}
		i++;
	}
}

void	ft_check_border(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->map_y)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (i == 0 || i == data->map->map_y - 1 || j == 0 \
			|| j == (int)ft_strlen(data->map->map[i]) - 1)
			{
				if (data->map->map[i][j] != '1' && data->map->map[i][j] != '*')
					ft_error("Map is not closed from border", data);
			}
			j++;
		}
		i++;
	}
}

void	get_new_map(t_data *data)
{
	char	**mapp;
	int		i;
	int		j;

	i = 0;
	mapp = malloc(sizeof(char *) * (data->map->map_y + 1));
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
}

void	ft_check_map(t_data *data)
{
	flood_fill(data, (int)data->ray->posy, (int)data->ray->posx);
	check_flood(data);
	check_player_amount(data);
	check_map_characters(data);
	get_new_map(data);
	ft_check_stars(data);
	ft_check_border(data);
}
