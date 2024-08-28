/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:30:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/27 12:17:05 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	calc_width(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i])
		i++;
	if (s[i - 1] == '\n')
		i--;
	return (i);
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

int	map_reading(t_map *game, char **s)
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
		game->width = calc_width(game->map[game->i++]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	game;

	if (argc != 2)
	{
		printf("Error\nWe need a map to play.\n");
		exit(0);
	}
	game.win_p = NULL;
	game.mlx_p = NULL;
	ft_bzero(&game, sizeof(t_map));
	game.x = 1000;
	game.y = 500;
	map_reading(&game, argv);
	parser(&game);
	game.mlx_p = mlx_init();
	game.win_p = mlx_new_window(game.mlx_p, 2048, 1024, "cub3d");
	mlx_pixel_put(game.mlx_p, game.win_p, 1024, 512, 0xFFFFFF);
	mlx_key_hook(game.win_p, deal_key, (void *)&game);
	mlx_hook(game.win_p, 17, 0, mouse_hook, (void *)&game);
	mlx_loop(game.mlx_p);
	return (0);
}
