/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:02:34 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/26 11:53:39 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char	s)
{
	if (s == '\0' || s == ' ' || s == '\n' || s == '\t')
		return(1);
	return(0);
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

	i = 0;
	game->per = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (((ft_isspace(map[i][j + 1]) || !map[i][j + 1]
					|| ft_isspace(map[i][j - 1])
					|| !map[i - 1] || !map[i - 1][j]
					|| ft_isspace(map[i - 1][j])) || !map[i + 1]
					|| !(map[i + 1][j]) || ft_isspace(map[i + 1][j]))
					&& (map[i][j] != '1' && !ft_isspace(map[i][j])))
			{
				printf("Error\nThe map is invalid\n");
				exit(0);
			}
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W')
			{
				if (game->per == 0)
					game->per = map[i][j];
				else
				{
				printf("Error\nIs a mission for a brave person, no for a team.\n");
				exit(0);
				}
			}
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
					&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
					&& !ft_isspace(map[i][j]))
			{
				printf("Error\nThat map is too strange.\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
	if (game->per == 0)
	{
		printf("Error\nFor this mission we need a brave person.\n");
		exit(0);
	}
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
		if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"NO ", 3))
			game->n_wall = ft_strdup(ft_no_spaces(game, i, "NO"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"SO ", 3))
			game->s_wall = ft_strdup(ft_no_spaces(game, i, "SO"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"WE ", 3))
			game->w_wall = ft_strdup(ft_no_spaces(game, i, "WE"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"EA ", 3))
			game->e_wall = ft_strdup(ft_no_spaces(game, i, "EA"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"F ", 2))
			game->floor = ft_strdup(ft_no_spaces(game, i, "F"));
		else if (game->map[i][j] && !ft_strncmp(&game->map[i][j],"C ", 2))
			game->ceiling = ft_strdup(ft_no_spaces(game, i, "C"));
		i++;
	}
	if (!game->map[i] && game->param != 6)
	{
		printf("Error\nWe need more parameters\n");
		exit(0);
	}
	map_parser(game, &game->map[i]);
	return(0);
}
