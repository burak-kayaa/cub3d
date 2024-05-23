/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:01 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/23 09:18:31 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_image_array(t_data *data)
{
	char	*line;
	char	*texture;
	int		i;

	data->map_fd = open(data->map_path, O_RDONLY);
	if (data->map_fd < 0)
		return (1);
	data->images = malloc(sizeof(t_images *) * (TOTAL_TEXTURES + 1));
	if (!data->images)
		return (1);
	i = 0;
	data->images[TOTAL_TEXTURES] = NULL;
	while (++i < 5)
	{
		line = get_next_line(data->map_fd);
		if (!line)
			return (1);
		texture = ft_strdup(line + 2);
		texture[ft_strlen(texture) - 1] = '\0';
		texture = ft_strtrim(texture, " ");
		free(line);
		if (ft_load_walls(data, texture, i))
			return (ft_free_images(data, i), 1);
	}
	return (ft_load_other_images(data, i), 0);
}

int	ft_create_main_image(t_data *data)
{
	data->mlx_img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
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
	free(get_next_line(data->map_fd));
	return (0);
}

int	ft_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
		SCREENWIDTH, SCREENHEIGHT, "mlx 42");
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
	data->map->map_x = 45;
	data->map->map_y = 17;
	data->map->map_s = data->map->map_x * data->map->map_y;
	if (ft_init_images(data))
		return (free(data->ray), free(data->map), free(data), 1);
	return (0);
}
