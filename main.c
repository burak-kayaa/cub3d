/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:10:46 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 02:11:05 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (printf("Error\n"), 0);
	data = malloc(sizeof(t_data));
	ft_init(data, argv[1]);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->pos_x, \
		data->pos_y, 0x00FF0000);
	mlx_loop_hook(data->mlx_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 3, 0, key_released, data);
	mlx_hook(data->win_ptr, 2, 0, key_pressed, data);
	mlx_hook(data->win_ptr, 17, 0, ft_exit, data);
	mlx_loop(data->mlx_ptr);
}
