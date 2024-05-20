/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:01 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/20 17:23:59 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_create_map(char *file)
{
	char		*line;
	char		*tmp;
	int		fd;
	char	**map;
	
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

static int	ft_init_images(t_data *data)
{
	int i;
	char *textures[5] = {"", "textures/text1.xpm", "textures/text2.xpm", "textures/text3.xpm", "textures/text4.xpm"};
	
	data->images = malloc(sizeof(t_images *) * (TOTAL_TEXTURES + 1));
	i = 1;
	while (i < TOTAL_TEXTURES + 1)
	{
		data->images[i] = malloc(sizeof(t_images));
		if (!data->images[i])
		{
			i = 1;
			while (i < TOTAL_TEXTURES + 1)
				free(data->images[i++]);
			return (free(data->images), 1);			
		}
		data->images[i]->img = mlx_xpm_file_to_image(data->mlx_ptr, textures[i], &data->images[i]->width, &data->images[i]->height);
		data->images[i]->addr = (int *)mlx_get_data_addr(data->images[i]->img, &data->images[i]->bits_per_pixel, &data->images[i]->line_length, &data->images[i]->endian);
		i++;
	}
	data->mlx_img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->images[0] = malloc(sizeof(t_images));
	if (!data->images[0])
	{
		i = 1;
		while (i < TOTAL_TEXTURES + 1)
			free(data->images[i++]);
		return (free(data->images), 1);
	}
	data->mlx_o_data = (int *)mlx_get_data_addr(data->mlx_img, &data->images[0]->bits_per_pixel, &data->images[0]->line_length, &data->images[0]->endian);
	return (0);
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
	ray->mapx = 0;
	ray->mapy = 0;
	ray->side = 0;
	ray->wall = 0;
	ray->raydirx = 0;
	ray->raydiry = 0;
	ray->log = malloc(sizeof(int *) * TOTAL_RAYS);
}

int	ft_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "mlx 42");
	data->w_pressed = 0;
	data->a_pressed = 0;
	data->s_pressed = 0;
	data->d_pressed = 0;
	data->left_pressed = 0;
	data->right_pressed = 0;
	data->ray = malloc(sizeof(t_ray));
	ft_init_ray(data->ray);
	data->map = malloc(sizeof(t_map));
	data->map->mapX = 38;
	data->map->mapY = 19;
	data->map->mapS = data->map->mapX * data->map->mapY;
	if (ft_init_images(data))
		return (free(data->ray), free(data->map), free(data), 1);
	return (0);
}
