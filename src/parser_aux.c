/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:31:38 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 09:33:05 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char s)
{
	if (s == '\0' || s == ' ' || s == '\n' || s == '\t')
		return (1);
	return (0);
}

int	ft_line_bef(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[i] && k != j)
	{
		if (map[i][k++] == '\0')
			return (0);
	}
	return (1);
}

char	*ft_no_spaces(t_map *game, int k, char *param)
{
	int		i;
	char	*line;

	line = game->map[k];
	i = 0;
	while (line[i] != param[0] && line[i + 1] != param[1])
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
	{
		game->param++;
		return (&line[i]);
	}
	return (NULL);
}
