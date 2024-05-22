/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:59:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 19:11:31 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture_helper(t_data *data)
{
	double	wallx;

	data->ray->texnum = data->map->map[data->ray->map_x][data->ray->map_y] - 1;
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
	data->ray->texpos = (data->ray->drawstart - 1080 / 2 + data->ray->lineheight
			/ 2) * data->ray->texstep;
}

void	ft_draw_wall_texture(t_data *data, int x, int tex_index)
{
	static int	i;
	int			texy;

	i = 0;
	while (data->ray->drawstart < data->ray->drawend)
	{
		texy = (int)data->ray->texpos & 63;
		data->ray->texpos += data->ray->texstep;
		if (i == 0)
			i++;
		if (i % 15 == 0)
			i = 1;
		if (texy >= 62)
			texy = 61;
		data->mlx_o_data[data->ray->drawstart * SCREENWIDTH + x]
			= data->images[tex_index]->addr[64 * texy + data->ray->tex_x];
		data->ray->drawstart++;
		i++;
	}
}

void	ft_draw_wall_side(t_data *data, int x)
{
	if (data->ray->side == 0 && data->ray->raydirx > 0)
		ft_draw_wall_texture(data, x, 1);
	else if (data->ray->side == 0 && data->ray->raydirx < 0)
		ft_draw_wall_texture(data, x, 2);
	else if (data->ray->side == 1 && data->ray->raydiry > 0)
		ft_draw_wall_texture(data, x, 3);
	else
		ft_draw_wall_texture(data, x, 4);
}

void	ft_texture(t_data *data, int x)
{
	ft_texture_helper(data);
	if (data->ray->wall == 1)
		ft_draw_wall_side(data, x);
	else if (data->ray->wall == 2)
		ft_draw_wall_texture(data, x, 5);
}
