/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:46:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/22 19:56:21 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_floor_ceiling(t_data *data)
{
	char	*floor;
	char	*ceiling;

	floor = get_next_line(data->map_fd);
	ceiling = get_next_line(data->map_fd);
	data->map->floor = ft_split(floor, ',');
	data->map->ceiling = ft_split(ceiling, ',');
	data->map->floor_color = ft_atoi(data->map->floor[0]) * 65536 + \
		ft_atoi(data->map->floor[1]) * 256 + ft_atoi(data->map->floor[2]);
	data->map->ceiling_color = ft_atoi(data->map->ceiling[0]) * 65536 + \
		ft_atoi(data->map->ceiling[1]) * 256 + ft_atoi(data->map->ceiling[2]);
	free(floor);
	free(ceiling);
}

void	ft_create_map(t_data *data)
{
	char		*line;
	char		*tmp;

	tmp = ft_strdup("");
	ft_get_floor_ceiling(data);
	while (1)
	{
		line = get_next_line(data->map_fd);
		if (!line)
			break ;
		tmp = ft_strjoin_gnl(tmp, line);
	}
	data->map->map = ft_split(tmp, '\n');
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
	ray->log = malloc(sizeof(int *) * TOTAL_RAYS);
}
