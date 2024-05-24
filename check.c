/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:58:03 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *file)
{
	int	i;

	i = 0;
	if (ft_strlen(file) < 5)
		return (1);
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || \
		file[i - 4] != '.')
		return (1);
	return (0);
}

int	ft_check_input(t_data *data, char **argv)
{
	int		i;

	(void)data;
	i = 0;
	if (check_extension(argv[1]))
		return (1);
	return (0);
}
