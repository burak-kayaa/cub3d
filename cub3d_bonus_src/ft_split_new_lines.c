/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:44 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/27 21:07:58 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_countwords(char const *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == '\n')
			i++;
		if (str[i] != '\n' && str[i] != '\0' \
		&& (i > 2 && str[i - 1] == '\n' && str[i - 2] == '\n'))
			count++;
		while (str[i] != '\n' && str[i] != '\0')
			i++;
	}
	count++;
	return (count);
}

char	**get_len_and_alloc(char **str)
{
	int		len;
	char	**tab;

	while ((**str) == '\n')
		(*str)++;
	len = ft_countwords(*str);
	if (len < 3)
		return (ft_error("Map is too small", NULL), NULL);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (ft_error("Malloc failed", NULL), NULL);
	return (tab);
}

static void	ft_split_helper(int *k, int *i, char *str)
{
	*k = *i - 2;
	while (str[(*i)] != '\0' \
	&& !((*i) >= 2 && str[(*i)] != '\n'
			&& str[(*i) - 1] == '\n' && str[(*i) - 2] == '\n'))
		(*i)++;
	while (str[(*i)] == '\n')
		(*i)++;
}

char	**ft_split_new_lines(char *str)
{
	char	**tab;
	int		i;
	int		k;
	int		tab_index;

	tab = get_len_and_alloc(&str);
	i = 2;
	tab_index = 0;
	k = 0;
	while (str[i])
	{
		ft_split_helper(&k, &i, str);
		if (i > k)
			tab[tab_index++] = ft_substr(str, k, i - k);
		if (str[i] == '\0')
			break ;
		while (str[i] && str[i] == '\n')
			i++;
		if (str[i] && !str[i + 1])
			tab[tab_index++] = ft_substr(str, i, 1);
		i++;
	}
	tab[tab_index] = NULL;
	return (tab);
}
