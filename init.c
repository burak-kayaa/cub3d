/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:01 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 19:09:53 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_load_image(t_data *data, char *texture, int index)
{
	data->images[index] = malloc(sizeof(t_images));
	if (!data->images[index])
		return (1);
	data->images[index]->img = mlx_xpm_file_to_image(data->mlx_ptr, \
		texture, &data->images[index]->width, &data->images[index]->height);
	data->images[index]->addr = \
	(int *)mlx_get_data_addr(data->images[index]->img, \
	&data->images[index]->bits_per_pixel, &data->images[index]->line_length, \
	&data->images[index]->endian);
	return (0);
}

int	ft_init_image_array(t_data *data)
{
	int		i;
	char	*textures[15] = {"", "textures/text1.xpm", "textures/text2.xpm", \
	"textures/text3.xpm", "textures/text4.xpm", "textures/fatih_kapi.xpm", \
	"textures/anime2.xpm", "textures/anime3.xpm", \
	"textures/anime4.xpm", "textures/anime5.xpm", "textures/anime6.xpm", \
	"textures/anime7.xpm", "textures/anime8.xpm", "textures/anime9.xpm", \
	"textures/anime10.xpm"};

	data->images = malloc(sizeof(t_images *) * (TOTAL_TEXTURES + 1));
	if (!data->images)
		return (1);
	data->images[TOTAL_TEXTURES] = NULL;
	i = 1;
	while (i < TOTAL_TEXTURES + 1)
	{
		if (ft_load_image(data, textures[i], i))
		{
			ft_free_images(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_create_main_image(t_data *data)
{
	data->mlx_img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->images[0] = malloc(sizeof(t_images));
	if (!data->images[0])
	{
		ft_free_images(data, TOTAL_TEXTURES + 1);
		return (1);
	}
	data->mlx_o_data = (int *)mlx_get_data_addr(data->mlx_img, \
	&data->images[0]->bits_per_pixel, &data->images[0]->line_length, \
	&data->images[0]->endian);
	return (0);
}

int	ft_init_images(t_data *data)
{
	if (ft_init_image_array(data))
		return (1);
	if (ft_create_main_image(data))
		return (1);
	return (0);
}

int	ft_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "mlx 42");
	data->w_pressed = 0;
	data->a_pressed = 0;
	data->s_pressed = 0;
	data->d_pressed = 0;
	data->e_pressed = 0;
	data->left_pressed = 0;
	data->right_pressed = 0;
	data->is_door_open = 0;
	data->ray = malloc(sizeof(t_ray));
	ft_init_ray(data->ray);
	data->map = malloc(sizeof(t_map));
	data->map->map_x = 38;
	data->map->map_y = 19;
	data->map->map_s = data->map->map_x * data->map->map_y;
	if (ft_init_images(data))
		return (free(data->ray), free(data->map), free(data), 1);
	return (0);
}
