/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:07:35 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/16 14:17:02 by burkaya          ###   ########.fr       */
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
# define TILE_SIZE 16
# define TOTAL_RAYS 1920
# define PLAYER_SPEED 1
# define PLAYER_SIZE 5
# define TOTAL_TEXTURES 4
# define DIR_NORTH 0
# define DIR_SOUTH 1
# define DIR_WEST 2
# define DIR_EAST 3

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

typedef struct s_images
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_images;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*mlx_img;
	int			*mlx_o_data;
	float		pos_x;
	float		pos_y;
	float		delta_x;
	float		delta_y;
	float		angle;
	t_bool		w_pressed;
	t_bool		a_pressed;
	t_bool		s_pressed;
	t_bool		d_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_map		*map;
	t_ray		*ray;
	t_images	**images;
}
				t_data;
void	ft_init(t_data *data, char *file);

/* MLX */
int	ft_exit(void *param);
int	key_hook(void *param);
int	key_pressed(int keycode, void *param);
int	key_released(int keycode, void *param);

/* UTILS */
void	ft_mlx_print_line(t_data *data, int x, int y, int x2, int y2, int color);
void	store_ray(t_data *data, int x, int y, int x2, int y2, int i);
void	ft_fill_floor_and_ceiling(t_data *data);
double	ft_ray_length(float x1, float y1, float x2, float y2);

/* RENDER */
void	ft_render_map(t_data *data, int render_fc);
int ft_player_move(t_data *data);
void ft_draw_square_on_coords(t_data *data, int x, int y, int color);
#endif