/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:21 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/30 17:53:51 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture_helper(t_data *data)
{
	double	wallx;

	if (data->ray->side == 0)
		wallx = data->ray->posy + data->ray->perpwalldist * data->ray->raydiry;
	else
		wallx = data->ray->posx + data->ray->perpwalldist * data->ray->raydirx;
	wallx -= floor(wallx);
	data->ray->tex_x = (int)(wallx * (double)64);
	if (data->ray->side == 0 && data->ray->raydirx > 0)
		data->ray->tex_x = 64 - data->ray->tex_x - 1;
	if (data->ray->side == 1 && data->ray->raydiry < 0)
		data->ray->tex_x = 64 - data->ray->tex_x - 1;
	data->ray->texstep = 1.0 * 64 / data->ray->lineheight;
	data->ray->texpos = (data->ray->drawstart - SCREENHEIGHT
			/ 2 + data->ray->lineheight / 2) * data->ray->texstep;
}

void	ft_draw_wall_texture(t_data *data, int x, int tex_index)
{
	int			texy;

	while (data->ray->drawstart < data->ray->drawend)
	{
		texy = (int)data->ray->texpos & 63;
		data->ray->texpos += data->ray->texstep;
		if (data->images[tex_index]->addr[64 * texy + data->ray->tex_x] > 0)
			data->mlx_o_data[data->ray->drawstart * SCREENWIDTH + x]
				= data->images[tex_index]->addr[64 * texy + data->ray->tex_x];
		data->ray->drawstart++;
	}
}

void	ft_draw_wall_side(t_data *data, int x)
{
	ft_texture_helper(data);
	if (data->ray->side == 0 && data->ray->raydirx > 0)
		ft_draw_wall_texture(data, x, 1);
	else if (data->ray->side == 0 && data->ray->raydirx < 0)
		ft_draw_wall_texture(data, x, 2);
	else if (data->ray->side == 1 && data->ray->raydiry > 0)
		ft_draw_wall_texture(data, x, 3);
	else
		ft_draw_wall_texture(data, x, 4);
}
