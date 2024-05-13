/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:07:35 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/13 22:25:00 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define TILE_SIZE 64
# define TOTAL_RAYS 60

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

typedef int t_bool;

typedef struct s_map
{
	int		mapX;
	int		mapY;
	int		mapS;
	char	**map;
}				t_map;

typedef struct s_ray
{
	float rayX;
	float rayY;
	float rayAngle;
	int	  **log;
}	t_ray;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	float	pos_x;
	float	pos_y;
	float	delta_x;
	float	delta_y;
	float	angle;
	t_bool	w_pressed;
	t_bool	a_pressed;
	t_bool	s_pressed;
	t_bool	d_pressed;
	t_bool	left_pressed;
	t_bool	right_pressed;
	t_map	*map;
	t_ray	*ray;
}
				t_data;
void	ft_init(t_data *data, char *file);

/* MLX */
int	ft_exit(void *param);
int	key_hook(void *param);
int	key_pressed(int keycode, void *param);
int	key_released(int keycode, void *param);
/* UTILS */
void ft_fill_pixel(t_data *data, int x, int y, char type);
void	ft_mlx_print_line(t_data *data, int x, int y, int x2, int y2, int color);
void	store_ray(t_data *data, int x, int y, int x2, int y2, int i);

/* RENDER */
void	ft_render_map(t_data *data);

#endif