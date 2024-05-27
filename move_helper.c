/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:09 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 05:26:46 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_character(t_data *data, int x, int y)
{
	char c;

	c = data->map->map[x][y];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'U')
		return (1);
	return (0);
}

void	key_w(t_data *data)
{
	if (data->map->map[(int)(data->ray->posx + data->ray->dirx
			* 0.15)][(int)(data->ray->posy)] == '0'
		|| is_character(data, (int)(data->ray->posx + data->ray->dirx * 0.15), (int)(data->ray->posy)))
		data->ray->posx += data->ray->dirx * 0.15;
	if (data->map->map[(int)data->ray->posx][(int)(data->ray->posy
		+ data->ray->diry * 0.15)] == '0'
		|| is_character(data, (int)data->ray->posx, (int)(data->ray->posy + data->ray->diry * 0.15)))
		data->ray->posy += data->ray->diry * 0.15;
}

void	key_s(t_data *data)
{
	if (data->map->map[(int)(data->ray->posx - data->ray->dirx
			* 0.15)][(int)(data->ray->posy)] == '0'
		|| is_character(data, (int)(data->ray->posx - data->ray->dirx * 0.15), (int)(data->ray->posy)))
		data->ray->posx -= data->ray->dirx * 0.15;
	if (data->map->map[(int)(data->ray->posx)][(int)(data->ray->posy
			- data->ray->diry * 0.15)] == '0'
		|| is_character(data, (int)(data->ray->posx), (int)(data->ray->posy - data->ray->diry * 0.15)))
		data->ray->posy -= data->ray->diry * 0.15;
}

void	key_d(t_data *data)
{
	if (data->map->map[(int)(data->ray->posx + data->ray->diry
			* 0.15)][(int)(data->ray->posy)] == '0'
		|| is_character(data, (int)(data->ray->posx + data->ray->diry * 0.15), (int)(data->ray->posy)))
		data->ray->posx += data->ray->diry * 0.15;
	if (data->map->map[(int)(data->ray->posx)][(int)(data->ray->posy
			- data->ray->dirx * 0.15)] == '0'
		|| is_character(data, (int)(data->ray->posx), (int)(data->ray->posy - data->ray->dirx * 0.15)))
		data->ray->posy -= data->ray->dirx * 0.15;
}

void	key_a(t_data *data)
{
	if (data->map->map[(int)(data->ray->posx - data->ray->diry
			* 0.15)][(int)(data->ray->posy)] == '0'
		|| is_character(data, (int)(data->ray->posx - data->ray->diry * 0.15), (int)(data->ray->posy)))
		data->ray->posx -= data->ray->diry * 0.15;
	if (data->map->map[(int)(data->ray->posx)][(int)(data->ray->posy
			+ data->ray->dirx * 0.15)] == '0'
		|| is_character(data, (int)(data->ray->posx), (int)(data->ray->posy + data->ray->dirx * 0.15)))
		data->ray->posy += data->ray->dirx * 0.15;
}
