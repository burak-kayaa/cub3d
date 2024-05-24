/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:52 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:57:51 by burkaya          ###   ########.fr       */
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
	}
	*result = tmp;
	return (0);
}

void	process_map_data(t_data *data, char *map_data)
{
	char	**t;
	char	**tmp2;
	char	*_2map;
	int		i;

	t = ft_split_new_lines(map_data);
	data->map->wall_textures = ft_split(t[0], '\n');
	tmp2 = ft_split(t[1], '\n');
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
}
