/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:59 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/30 17:02:50 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_load_walls(t_data *data, char *texture, int index)
{
	data->images[index] = malloc(sizeof(t_images));
	if (!data->images[index])
		return (1);
	data->images[index]->img = mlx_xpm_file_to_image(data->mlx_ptr, \
		texture, &data->images[index]->width, &data->images[index]->height);
	if (!data->images[index]->img)
		return (1);
	data->images[index]->addr = \
	(int *)mlx_get_data_addr(data->images[index]->img, \
	&data->images[index]->bits_per_pixel, &data->images[index]->line_length, \
	&data->images[index]->endian);
	free(texture);
	return (0);
}

void	ft_load_image(t_data *data, char *texture, int index)
{
	data->images[index] = malloc(sizeof(t_images));
	if (!data->images[index])
	{
		ft_free_images(data, index);
		return ;
	}
	data->images[index]->img = mlx_xpm_file_to_image(data->mlx_ptr, \
	texture, &data->images[index]->width, &data->images[index]->height);
	data->images[index]->addr = \
	(int *)mlx_get_data_addr(data->images[index]->img, \
	&data->images[index]->bits_per_pixel, &data->images[index]->line_length, \
	&data->images[index]->endian);
}
