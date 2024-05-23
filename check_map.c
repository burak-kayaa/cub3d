/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 14:28:48 by burkaya          ###   ########.fr       */
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

int	map_wall_check(t_data *data, char c)
{
	if (c == ' ')
		return (1);
	else
		ft_error("Map is not closed", data);
	return (0);
}

void	check_up_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[0][i] && data->map->map[0][i] != '\n')
	{
		if (data->map->map[0][i] == '1')
			i++;
		else if (data->map->map[0][i] == ' ')
		{
			j = 0;
			while (j < data->map->map_x)
			{
				if (data->map->map[j][i] == '1')
				{
					i++;
					break ;
				}
				else
					j += map_wall_check(data, data->map->map[j][i]);
			}
			i += j;
		}
		else
			ft_error("Map is not closed from up", data);
	}
}

int	down_wall(t_data *data, int i)
{
	int	j;

	j = data->map->map_y - 1;
	while (data->map->map[j][i])
	{
		if (data->map->map[j][i] == '1')
		{
			i++;
			break ;
		}
		else
			j -= map_wall_check(data, data->map->map[j][i]);
	}
	return (i);
}

void	check_down_wall(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->map[data->map->map_y - 1][i] && data->map->map[data->map->map_y - 1][i] != '\n')
	{
		if (data->map->map[data->map->map_y - 1][i] == '1')
			i++;
		else if (data->map->map[data->map->map_y - 1][i] == ' ')
			i = down_wall(data, i);
		else
			ft_error("Map is not closed from down", data);
	}
}

void	check_left_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i][0] && i < data->map->map_y - 1)
	{
		if (data->map->map[i][0] == '1')
			i++;
		else if (data->map->map[i][0] == ' ')
		{
			j = 0;
			while (data->map->map[i][j])
			{
				if (data->map->map[i][j] == '1')
				{
					i++;
					break ;
				}
				else
					j += map_wall_check(data, data->map->map[i][j]);
			}
		}
		else
			ft_error("Map is not closed from left", data);
	}
}

int	right_wall(t_data *data, int i, int k)
{
	if (i - 1 >= 0 && ft_strlen(data->map->map[i]) > ft_strlen(data->map->map[i - 1]))
		k = ft_strlen(data->map->map[i - 1]) - 1;
	if (i + 1 < data->map->map_y - 1 && i - 1 >= 0
		&& ft_strlen(data->map->map[i]) > ft_strlen(data->map->map[i + 1])
		&& ft_strlen(data->map->map[i + 1]) < ft_strlen(data->map->map[i - 1]))
		k = ft_strlen(data->map->map[i + 1]) - 1;
	if (i + 1 == data->map->map_y - 1
		&& ft_strlen(data->map->map[i]) > ft_strlen(data->map->map[i + 1])
		&& ft_strlen(data->map->map[i + 1]) < ft_strlen(data->map->map[i - 1]))
		k = ft_strlen(data->map->map[i + 1]);
	return (k);
}

void	check_right_wall(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = ft_strlen(data->map->map[0]) - 2;
	while (i < data->map->map_y && data->map->map[i])
	{
		j = ft_strlen(data->map->map[i]) - 1;
		if (data->map->map[i][j] == '\n')
			j--;
		while (data->map->map[i][j] && data->map->map[i][j] == ' ')
			j--;
		k = right_wall(data, i, k);
		while (k < j)
		{
			if (data->map->map[i][k] && data->map->map[i][k] != '1')
				ft_error("Map is not closed from right", data);
			k++;
		}
		if (data->map->map[i][j] && data->map->map[i][j] != '1')
			ft_error("Map is not closed from right", data);
		i++;
	}
}

int	player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	space_validation(t_data *data, int i, int j)
{
	if (j + 1 < (int)ft_strlen(data->map->map[i]) && (data->map->map[i][j + 1] == '0'
		|| player(data->map->map[i][j + 1])))
		ft_error("Spaces in the wrong place", data);
	else if (j > 0 && (data->map->map[i][j - 1] == '0' || player(data->map->map[i][j - 1])))
		ft_error("Spaces in the wrong place", data);
	else if (i < data->map->map_y && (data->map->map[i][j] == '0'
		|| player(data->map->map[i][j])))
		ft_error("Spaces in the wrong place", data);
	else if (i > 0 && (data->map->map[i][j] == '0' || player(data->map->map[i][j])))
		ft_error("Spaces in the wrong place", data);
}

void	check_spaces(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->map_x && data->map->map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(data->map->map[i]))
		{
			if (data->map->map[i][j] == ' ')
				space_validation(data, i, j);
			j++;
		}
	}
}

void	ft_check_map(t_data *data)
{
	check_up_wall(data);
	check_down_wall(data);
	check_left_wall(data);
	check_right_wall(data);
	check_spaces(data);
}