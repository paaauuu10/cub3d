/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/29 11:35:45 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

int	mouse_hook(t_map *game)
{
	(void)game;
	exit(0);
	return (0);
}
