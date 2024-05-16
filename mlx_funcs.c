/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:59:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 13:54:31 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	key_hook(void *param)
{
	t_data	*data;
	int	n;
	data = (t_data *)param;
	ft_render_map(data, 1);
	if (ft_player_move(data))
		return (1);
	n = 0;
	while (n < TOTAL_RAYS)
	{
		if (data->ray->log == NULL)
			break;
		if (data->ray->log[n] != NULL)
			ft_mlx_print_line(data, data->ray->log[n][0], data->ray->log[n][1], data->ray->log[n][2], data->ray->log[n][3], 0x00000000);
		n++;
	}
	n = 0;
	data->ray->log = malloc(sizeof(int *) * TOTAL_RAYS);
	while (n < TOTAL_RAYS)
	{
		float x = data->pos_x;
		float y = data->pos_y;
		float x2 = data->pos_x + data->delta_x * 10;
		float y2 = data->pos_y + data->delta_y * 10;
		float angle = data->angle - (M_PI / 6) + (M_PI / 3) * n / TOTAL_RAYS;
		data->ray->rayAngle = angle;
		float delta_x = cos(angle) * 5;
		float delta_y = sin(angle) * 5;
		x2 = data->pos_x + delta_x * 200;
		y2 = data->pos_y + delta_y * 200;
		ft_mlx_print_line(data, x, y, x2, y2, n);
		n++;
	}
	ft_render_map(data, 0);
	ft_draw_square_on_coords(data, data->pos_x, data->pos_y, PLAYER_SIZE, 0x0000FF00);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img, 0, 0);
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC_KEY)
		ft_exit(data);
	if (keycode == W_KEY)
		data->w_pressed = 1;
	if (keycode == A_KEY)
		data->a_pressed = 1;
	if (keycode == S_KEY)
		data->s_pressed = 1;
	if (keycode == D_KEY)
		data->d_pressed = 1;
	if (keycode == LEFT_ARROW)
		data->left_pressed = 1;
	if (keycode == RIGHT_ARROW)
		data->right_pressed = 1;
	return (0);
}

int	key_released(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == W_KEY)
		data->w_pressed = 0;
	if (keycode == A_KEY)
		data->a_pressed = 0;
	if (keycode == S_KEY)
		data->s_pressed = 0;
	if (keycode == D_KEY)
		data->d_pressed = 0;
	if (keycode == LEFT_ARROW)
		data->left_pressed = 0;
	if (keycode == RIGHT_ARROW)
		data->right_pressed = 0;
	return (0);
}