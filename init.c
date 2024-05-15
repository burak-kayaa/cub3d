/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:01 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 02:07:05 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**ft_create_map(char *file)
{
	char		*line;
	char		*tmp;
	int		fd;
	char	**map;
	
	line = ft_strdup("31");
	tmp = ft_strdup("");
	fd = open(file, O_RDONLY);
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

static void	ft_init_images(t_data *data)
{
	int i;
	char *textures[5] = {"", "textures/text1.xpm", "textures/text2.xpm", "textures/text3.xpm", "textures/text4.xpm"};
	
	data->images = malloc(sizeof(t_images *) * (TOTAL_TEXTURES + 1));
	i = 1;
	while (i < TOTAL_TEXTURES + 1)
	{
		data->images[i] = malloc(sizeof(t_images));
		data->images[i]->img = mlx_xpm_file_to_image(data->mlx_ptr, textures[i], &data->images[i]->width, &data->images[i]->height);
		data->images[i]->addr = (int *)mlx_get_data_addr(data->images[i]->img, &data->images[i]->bits_per_pixel, &data->images[i]->line_length, &data->images[i]->endian);
		i++;
	}
	data->mlx_img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->images[0] = malloc(sizeof(t_images));
	data->mlx_o_data = (int *)mlx_get_data_addr(data->mlx_img, &data->images[0]->bits_per_pixel, &data->images[0]->line_length, &data->images[0]->endian);
}

void	ft_init(t_data *data, char *file)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "mlx 42");
	data->pos_x = 64;
	data->pos_y = 32;
	data->w_pressed = 0;
	data->a_pressed = 0;
	data->s_pressed = 0;
	data->d_pressed = 0;
	data->left_pressed = 0;
	data->right_pressed = 0;
	data->ray = malloc(sizeof(t_ray));
	data->ray->log = NULL;
	data->angle = 0.01;
	data->delta_x = cos(data->angle) * 5;
	data->delta_y = sin(data->angle) * 5;
	data->map = malloc(sizeof(t_map));
	data->map->mapX = 38;
	data->map->mapY = 19;
	data->map->mapS = data->map->mapX * data->map->mapY;
	data->map->map = ft_create_map(file);
	ft_init_images(data);
}
