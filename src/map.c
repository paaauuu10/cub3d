/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:02:34 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 09:27:36 by pborrull         ###   ########.fr       */
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

int	map_parser(t_map *game, char **map)
{
	int	i;
	int	j;

	game->per = 0;
	i = 1;
	j = 0;
	if (map[0] && map[0][0] && map[0][0] != '1' && !ft_isspace(map[0][j]))
		ft_exit(game, "You cannot begin like that.");
	while (map[0] && map[0][j] && (map[0][j] == '1'
			|| ft_isspace(map[0][j])))
	{
		j++;
		if (map[0][j] && map[0][j] != '1' && !ft_isspace(map[0][j]))
			ft_exit(game, "Bad first line");
	}
	while (map[i])
	{
		if (map[i][0] != '1' && !ft_isspace(map[i][0]))
			ft_exit(game, "The map is invalid-");
		j = 1;
		while (map[i][j])
		{
			if (((ft_isspace(map[i][j + 1]) || !map[i][j + 1] || !ft_line_bef(map, i + 1, j)
				|| ft_isspace(map[i][j - 1]) || !ft_line_bef(map, i - 1, j)
					|| ft_isspace(map[i - 1][j])) || !map[i + 1]
					|| !(map[i + 1][j]) || ft_isspace(map[i + 1][j]))
					&& (map[i][j] != '1' && !ft_isspace(map[i][j])))
				ft_exit(game, "The map is invalid");
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W')
			{
				if (game->per == 0)
					game->per = map[i][j];
				else
					ft_exit(game, "That mission is not for a team.");
			}
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
					&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
					&& !ft_isspace(map[i][j]))
				ft_exit(game, "That map is too strange.");
			j++;
		}
		i++;
	}
	if (game->per == 0)
		ft_exit(game, "For this mission we need a brave person.");
	return (0);
}

void	ft_parser_aux(t_map *game, int i, int j)
{
	if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "NO ", 3))
			game->n_wall = ft_strdup(ft_no_spaces(game, i, "NO"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "SO ", 3))
			game->s_wall = ft_strdup(ft_no_spaces(game, i, "SO"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "WE ", 3))
			game->w_wall = ft_strdup(ft_no_spaces(game, i, "WE"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "EA ", 3))
			game->e_wall = ft_strdup(ft_no_spaces(game, i, "EA"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "F ", 2))
			game->floor = ft_strdup(ft_no_spaces(game, i, "F"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j], "C ", 2))
			game->ceiling = ft_strdup(ft_no_spaces(game, i, "C"));
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
		ft_parser_aux(game, i, j);
		i++;
	}
	if (!game->map[i] && game->param != 6)
		ft_exit(game, "We need more parameters");
	map_parser(game, &game->map[i]);
	return (0);
}
