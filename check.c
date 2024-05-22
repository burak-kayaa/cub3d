/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:03:22 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/21 16:32:26 by codespace        ###   ########.fr       */
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
