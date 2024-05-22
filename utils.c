/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:01:03 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/21 22:25:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_floor_and_ceiling(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < 1080 / 2)
	{
		n = 0;
		while (n < 1920)
		{
			data->mlx_o_data[i * 1920 + n] = 0x00575757;
			n++;
		}
		i++;
	}
	while (i < 1080)
	{
		n = 0;
		while (n < 1920)
		{
			data->mlx_o_data[i * 1920 + n] = 0x005b95b0;
			n++;
		}
		i++;
	}
}
