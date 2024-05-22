/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:59:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/22 01:35:05 by egumus           ###   ########.fr       */
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
	ft_render_map(data, 1);
	ft_move(data);
	ft_ray_casting(data);
	ft_render_map(data, 0);
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
	if (keycode == E_KEY)
		data->e_pressed = 1;
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
	if (keycode == E_KEY)
		data->e_pressed = 0;
	return (0);
}