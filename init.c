/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:16:01 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/13 21:38:39 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_tab_len(char **tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tab[i])
	{
		while (tab[i][j])
			j++;
		i++;
	}
	return (j);
}

static char	**ft_create_map(char *file)
{
	char		*line;
	char		*tmp;
	int		fd;
	char	**map;
	
	line = ft_strdup("31");
	tmp = ft_strdup("");
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin_gnl(tmp, line);
	}
	map = ft_split(tmp, '\n');
	return (map);
}

void	ft_print_tap(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_init(t_data *data, char *file)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 64 * 8, 64 * 8, "mlx 42");
	data->pos_x = 100;
	data->pos_y = 100;
	data->w_pressed = 0;
	data->a_pressed = 0;
	data->s_pressed = 0;
	data->d_pressed = 0;
	data->left_pressed = 0;
	data->right_pressed = 0;
	data->ray = malloc(sizeof(t_ray));
	data->ray->log = NULL;
	data->angle = 0.01;
	data->delta_x = cos(data->angle) * 5;
	data->delta_y = sin(data->angle) * 5;
	data->map = malloc(sizeof(t_map));
	data->map->mapX = 8;
	data->map->mapY = 8;
	data->map->mapS = data->map->mapX * data->map->mapY;
	data->map->map = ft_create_map(file);
	ft_print_tap(data->map->map);
}
