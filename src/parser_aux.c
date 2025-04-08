/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:31:38 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 09:44:57 by pborrull         ###   ########.fr       */
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

int	ft_get_color_component(t_map *game, char **s)
{
	int	num;

	num = 0;
	while (ft_isspace(**s))
		(*s)++;
	while (ft_isdigit(**s) && **s != ',')
		num = num * 10 + (*((*s)++) - '0');
	if (**s != ',' && **s != ' ' && **s != '\n')
		ft_exit(game, "One parameter or more are incorrect");
	return (num);
}

int	ft_obtcolor(t_map *game, char *s)
{
	int		red;
	int		green;
	int		blue;
	char	*temp;

	temp = s;
	s++;
	red = ft_get_color_component(game, &s);
	if (*s == ',')
		s++;
	green = ft_get_color_component(game, &s);
	if (*s == ',')
		s++;
	blue = ft_get_color_component(game, &s);
	if (*s != '\n')
		ft_exit(game, "One parameter or more are incorrect");
	return (free(temp), red * 65536 + green * 256 + blue);
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
