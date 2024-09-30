/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 14:14:56 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calc_width(t_map *game, char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (game->width);
	while (s[i])
		i++;
	if (s[i - 1] == '\n')
		i--;
	if (game->width < i)
		return (i);
	return (game->width);
}

int	add_lines(t_map *game, char *line)
{
	char	**temp;
	int		i;

	i = 0;
	game->height++;
	temp = (char **)malloc((game->height + 1) * sizeof(char *));
	if (!temp)
		ft_exit(game, NULL);
	temp[game->height] = NULL;
	while (i < game->height - 1)
	{
		temp[i] = game->map[i];
		i++;
	}
	temp[i] = line;
	if (game->map)
		free(game->map);
	game->map = temp;
	return (1);
}

int	ft_map_reading(t_map *game, char **s)
{
	char	*line;

	game->i = 0;
	game->fd = open(s[1], O_RDONLY);
	if (game->fd < 0)
		ft_exit(game, "We need a valid file");
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			add_lines (game, line);
		else
			free(line);
	}
	close (game->fd);
	if (!game->map)
		ft_exit(game, "I need a valid map");
	while (game->map[game->i])
		game->width = calc_width(game, game->map[game->i++]);
	return (1);
}
