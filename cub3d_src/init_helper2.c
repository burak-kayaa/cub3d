/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:52 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/30 18:28:39 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_multiple_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	read_and_concatenate_map(int fd, char **result)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin_gnl(tmp, line);
		free(line);
	}
	*result = tmp;
	return (0);
}

int	process_map_data(t_data *data, char *map_data)
{
	char	**t;
	char	**tmp2;
	char	*_2map;
	int		i;

	t = ft_split_new_lines(map_data);
	data->map->wall_textures = ft_split(t[0], '\n');
	if (ft_tab_len(data->map->wall_textures) != 4)
		return (ft_free_array(t), free(map_data), 1);
	tmp2 = ft_split(t[1], '\n');
	if (ft_tab_len(tmp2) != 2)
		return (ft_free_array(t), ft_free_array(tmp2), free(map_data), 1);
	data->map->floor_str = ft_strdup(tmp2[0]);
	data->map->ceiling_str = ft_strdup(tmp2[1]);
	i = 2;
	_2map = ft_strdup("");
	while (t[i])
	{
		_2map = ft_strjoin_gnl(_2map, t[i]);
		i++;
	}
	data->map->map_str = ft_strtrim(_2map, "\n");
	ft_free_array(t);
	ft_free_array(tmp2);
	return (free(map_data), free(_2map), 0);
}

int	ft_check_and_load_wall_textures(t_data *data, char *line)
{
	char	*texture;
	char	*texture_tmp;
	int		err;

	err = 0;
	texture_tmp = ft_strdup(line + 2);
	texture = ft_strtrim(texture_tmp, " ");
	free(texture_tmp);
	if (ft_strncmp(line, "NO", 2) == 0)
		err = ft_load_walls(data, texture, 1);
	else if (ft_strncmp(line, "SO", 2) == 0)
		err = ft_load_walls(data, texture, 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		err = ft_load_walls(data, texture, 3);
	else if (ft_strncmp(line, "EA", 2) == 0)
		err = ft_load_walls(data, texture, 4);
	else
	{
		free(texture);
		return (1);
	}
	return (err);
}
