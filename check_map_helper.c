/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:17 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:58:06 by burkaya          ###   ########.fr       */
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
