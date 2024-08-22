/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:02:34 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/22 11:27:54 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_no_spaces(char *line, char *param)
{
	int	i;

	i = 0;
	while (line[i] != param[0] || line[i + 1] != param[1])
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
	{
		game->param++;
		return (&line[i])
	}
	return (NULL);
}

int	map_parser(char	**map)
{

	return(0);
}

int	parser(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] && game->param != 6)
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] == ' ')
			j++;
		if (game->map[i][j] && ft_strncmp(game->map[i][j],"NO", 2))
			map->n_wall = ft_strdup(ft_no_spaces(game->map[i], "NO"));
		else if (game->map[i][j] && ft_strncmp(game->map[i][j],"SO", 2))
			map->s_wall = ft_strdup(ft_no_spaces(game->map[i], "SO"));
		else if (game->map[i][j] && ft_strncmp(game->map[i][j],"WE", 2))
			map->w_wall = ft_strdup(ft_no_spaces(game->map[i], "WE"));
		else if (game->map[i][j] && ft_strncmp(game->map[i][j],"EA", 2))
			map->e_wall = ft_strdup(ft_no_spaces(game->map[i], "EA"););
		else if (game->map[i][j] && ft_strncmp(game->map[i][j],"F", 2))
			map->floor = ft_strdup(ft_no_spaces(game->map[i], "F");
		else if (game->map[i][j] && ft_strncmp(game->map[i][j],"C", 2))
			map->ceiling = ft_strdup(ft_no_spaces(game->map[i], "C"));
		i++;
	}
	map_parser(&game->map[i]);
	return(0);
}
