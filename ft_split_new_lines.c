/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:56:44 by burkaya           #+#    #+#             */
/*   Updated: 2024/05/24 16:57:54 by burkaya          ###   ########.fr       */
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

char	**ft_split_new_lines(char const *str)
{
	char	*s;
	char	**tab;
	int		i;
	int		k;
	int		tab_index;
	int		len;

	i = 0;
	s = (char *)str;
	while (s[i] == '\n')
		i++;
	s += i;
	s = ft_strdup(s);
	len = ft_countwords(s);
	if (len < 3)
		return (ft_error("Error\n", NULL), NULL);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	i = 2;
	tab_index = 0;
	k = 0;
	while (s[i])
	{
		k = i - 2;
		while (s[i] != '\0' \
		&& !(i >= 2 && s[i - 1] == '\n' && s[i - 2] == '\n'))
			i++;
		while (s[i] == '\n')
			i++;
		if (i > k)
			tab[tab_index++] = ft_substr(s, k, i - k);
		if (s[i] == '\0')
			break ;
		i++;
		while (s[i] == '\n')
			i++;
	}
	tab[tab_index] = NULL;
	return (tab);
}
