/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 17:23:26 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *file)
{
	int	i;

	i = 0;
	if (ft_strlen(file) < 5)
		return (ft_error("Invalid file extension", NULL), 0);
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || \
		file[i - 4] != '.')
		return (ft_error("Invalid file extension", NULL), 0);
	return (0);
}
