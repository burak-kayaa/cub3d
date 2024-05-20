/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:07:35 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/20 19:14:04 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define E_KEY 14
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define TILE_SIZE 16
# define TOTAL_RAYS 1920
# define PLAYER_SIZE 5
# define TOTAL_TEXTURES 14
# define SCREENHEIGHT 1080
# define SCREENWIDTH 1920

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
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			key_w;
	int			key_s;
	int			key_left;
	int			key_right;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	double		sidedistx;
	double		sidedisty;
	int			wall;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			tex_x;
	int			texnum;
	double		texstep;
	double		texpos;
	int			key_a;
	int			key_d;
	int			**log;
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
	t_bool		w_pressed;
	t_bool		a_pressed;
	t_bool		s_pressed;
	t_bool		d_pressed;
	t_bool		e_pressed;
	t_bool		is_door_open;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_map		*map;
	t_ray		*ray;
	t_images	**images;
}t_data;

int	ft_init(t_data *data);

/* PARSE */
int	ft_check_input(t_data *data, char **argv);
char	**ft_create_map(char *file);

/* MLX */
int	ft_exit(void *param);
int	key_hook(void *param);
int	key_pressed(int keycode, void *param);
int	key_released(int keycode, void *param);

/* UTILS */
void	store_ray(t_data *data, int x, int y, int x2, int y2, int i);
void	ft_fill_floor_and_ceiling(t_data *data);
double	ft_ray_length(float x1, float y1, float x2, float y2);

/* RENDER */
void	ft_render_map(t_data *data, int render_fc);
int ft_player_move(t_data *data);
void ft_draw_square_on_coords(t_data *data, int x, int y, int color);
void	ft_ray_casting(t_data *data);
void	ft_texture(t_data *data, int x);
#endif