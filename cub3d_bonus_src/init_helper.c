/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:48 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/25 11:33:52 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_floor_ceiling(t_data *data)
{
	char	**tmp_floor;
	char	**tmp_ceiling;
	int		i;

	i = -1;
	tmp_floor = ft_split(data->map->floor_str, ' ');
	tmp_ceiling = ft_split(data->map->ceiling_str, ' ');
	if (ft_tab_len(tmp_floor) != 2 || ft_tab_len(tmp_ceiling) != 2
		|| ft_strcmp(tmp_floor[0], "F") || ft_strcmp(tmp_ceiling[0], "C"))
		ft_error("Invalid floor or ceiling color", data);
	data->map->floor = ft_split(data->map->floor_str + 2, ',');
	data->map->ceiling = ft_split(data->map->ceiling_str + 2, ',');
	while (++i < 3)
	{
		if (ft_atoi(data->map->floor[i]) > 255
			|| ft_atoi(data->map->ceiling[i]) > 255
			|| ft_atoi(data->map->floor[i]) < 0
			|| ft_atoi(data->map->ceiling[i]) < 0)
			ft_error("zort", data);
	}
	data->map->floor_color = ft_atoi(data->map->floor[0]) * 65536 + \
		ft_atoi(data->map->floor[1]) * 256 + ft_atoi(data->map->floor[2]);
	data->map->ceiling_color = ft_atoi(data->map->ceiling[0]) * 65536 + \
		ft_atoi(data->map->ceiling[1]) * 256 + ft_atoi(data->map->ceiling[2]);
}

int	ft_get_longest_index(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	ft_create_map(t_data *data)
{
	ft_get_floor_ceiling(data);
	if (ft_is_multiple_map(data->map->map_str))
		ft_error("Multiple maps", data);
	data->map->map = ft_split(data->map->map_str, '\n');
	data->map->flood_fill = ft_split(data->map->map_str, '\n');
	data->map->map_x = ft_get_longest_index(data->map->map);
	data->map->map_y = ft_tab_len(data->map->map);
}

void	ft_free_images(t_data *data, int max)
{
	int	i;

	i = 1;
	while (i < max)
	{
		if (data->images[i])
			free(data->images[i]);
		i++;
	}
	free(data->images);
}

void	ft_init_ray(t_ray *ray)
{
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->perpwalldist = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side = 0;
	ray->wall = 0;
	ray->raydirx = 0;
	ray->raydiry = 0;
}
