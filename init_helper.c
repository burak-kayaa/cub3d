/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:46:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/21 21:47:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_create_map(char *file)
{
	char		*line;
	char		*tmp;
	int			fd;
	char		**map;

	line = ft_strdup("31");
	tmp = ft_strdup("");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin_gnl(tmp, line);
	}
	map = ft_split(tmp, '\n');
	return (map);
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
