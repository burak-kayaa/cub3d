/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:59:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/13 22:26:50 by burkaya          ###   ########.fr       */
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

	data = (t_data *)param;

	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->pos_x, data->pos_y, 0x00000000);
	// if (keycode == ESC_KEY)
	// 	ft_exit(data);
	if (data->w_pressed)
		data->pos_y -= 2.5;
	if (data->a_pressed)
		data->pos_x -= 2.5;
	if (data->s_pressed)
		data->pos_y += 2.5;
	if (data->d_pressed)
		data->pos_x += 2.5;
	if (data->left_pressed)
	{
		data->angle -= 0.1;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		data->delta_x = cos(data->angle) * 5;
		data->delta_y = sin(data->angle) * 5;
	}
	if (data->right_pressed)
	{
		data->angle += 0.1;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		data->delta_x = cos(data->angle) * 5;
		data->delta_y = sin(data->angle) * 5;
	}
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->pos_x, data->pos_y, 0x00FF0000);
	// printf("data->pos_x + data->delta_x * 10: %f | data->pos_y + data->delta_y * 10: %f\n", data->pos_x + data->delta_x * 10, data->pos_y + data->delta_y * 10);
	int n = 0;
	// int pov = 60;
	while (n < TOTAL_RAYS)
	{
		if (data->ray->log == NULL)
			break;
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
		float angle = data->angle - 0.15 + (0.3 / TOTAL_RAYS) * n;
		float delta_x = cos(angle) * 5;
		float delta_y = sin(angle) * 5;
		x2 = data->pos_x + delta_x * 200;
		y2 = data->pos_y + delta_y * 200;
		ft_mlx_print_line(data, x, y, x2, y2, 0x00FF0000);
		store_ray(data, x, y, x2, y2, n);
		n++;
	}
	
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
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