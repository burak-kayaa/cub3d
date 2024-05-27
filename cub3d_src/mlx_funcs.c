/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:57:05 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/25 11:40:06 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_free_data(data);
	system("killall afplay");
	exit(0);
	return (0);
}

int	key_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_render_map(data, 1);
	if (ft_player_move(data))
		return (1);
	ft_ray_casting(data);
	ft_render_map(data, 0);
	ft_render_hand(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img, 0, 0);
	return (0);
}

int	mouse_hook(t_data *data)
{
	int	*x;
	int	*y;

	x = malloc(sizeof(int));
	y = malloc(sizeof(int));
	mlx_mouse_get_pos(data->win_ptr, x, y);
	if (*x > SCREENWIDTH / 2 + 100)
	{
		data->right_mouse_pressed = 1;
		data->left_mouse_pressed = 0;
	}
	else if (*x < SCREENWIDTH / 2 - 100)
	{
		data->left_mouse_pressed = 1;
		data->right_mouse_pressed = 0;
	}
	else
	{
		data->left_mouse_pressed = 0;
		data->right_mouse_pressed = 0;
	}
	return (free(x), free(y), 0);
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
