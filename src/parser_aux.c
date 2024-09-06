/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:31:38 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/05 11:10:21 by pborrull         ###   ########.fr       */
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

int	ft_obtain_color(char *s)
{
	int		i;
	int		red;
	int		green;
	int		blue;
	int		num;

	i = 1;
	num = 0;
	while (ft_isspace(s[i]))
		i++;
	while (!ft_isspace(s[i]) && ft_isdigit(s[i]) && s[i] != ',')
		num = num * 10 + (s[i++] - '0');
	red = num;
	num = 0;
	i++;
	while (!ft_isspace(s[i]) && ft_isdigit(s[i]) && s[i] != ',')
		num = num * 10 + (s[i++] - '0');
	green = num;
	num = 0;
	i++;
	while (!ft_isspace(s[i]) && ft_isdigit(s[i]) && s[i] != ',')
		num = num * 10 + (s[i++] - '0');
	blue = num;
	num = 0;
	return (red * 65536 + green * 256 + blue);
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
