/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/13 12:55:40 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int	deal_key(int key, t_map *game)
{
	if (key == 65307)
		ft_exit(game, "Why are you scared?");
	if ((key == 65361 || key == 97)
		&& (game->map_pos[game->y][game->x - 1] != '1'))
		game->x -= 1;
	if ((key == 65363 || key == 100)
		&& (game->map_pos[game->y][game->x + 1] != '1'))
		game->x += 1;
	if ((key == 65362 || key == 119)
		&& (game->map_pos[game->y - 1][game->x] != '1'))
		game->y -= 1;
	if ((key == 65364 || key == 115)
		&& (game->map_pos[game->y + 1][game->x] != '1'))
		game->y += 1;
	draw_map(game);
	return (0);
}*/

void	deal_key_aux(int key, t_map *game)
{
	if (key == 65361 || key == 97)
	{
		if (game->map_pos[game->y_pos / 32][(game->x_pos - 14) / 32] != '1')
			game->x_pos -= 4;
	}
	if (key == 65363 || key == 100)
	{
		if (game->map_pos[game->y_pos / 32][(game->x_pos + 4) / 32] != '1')
			game->x_pos += 4;
	}
	game->x = game->x_pos / TILE_SIZE;
	if (key == 65362 || key == 119)
	{
		if (game->map_pos[(game->y_pos - 14) / 32][(game->x_pos) / 32] != '1')
			game->y_pos -= 4;
	}
	if (key == 65364 || key == 115)
	{
		if (game->map_pos[(game->y_pos + 2) / 32][(game->x_pos) / 32] != '1')
			game->y_pos += 4;
	}
	game->y = game->y_pos / TILE_SIZE;
}

int	deal_key(int key, t_map *game)
{
	if (key == 65307)
		ft_exit(game, "Why are you scared?");
	deal_key_aux(key, game);
	printf("X: %d\n", game->x);
	printf("Y: %d\n", game->y);
	draw_map(game);
	ft_draw_player(game, 1);
	ft_draw_lines(game);
	return (0);
}

int	mouse_hook(t_map *game)
{
	(void)game;
	exit(0);
	return (0);
}
