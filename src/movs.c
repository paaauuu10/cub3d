/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/06 12:50:48 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	deal_key(int key, t_map *game)
{
	printf("X_pos: %d\n", game->x_pos / 32);
	printf("Y_pos: %d\n", game->y_pos / 32);
	if (key == 65307)
		ft_exit(game, "Why are you scared?");
	if (key == 65361 || key == 97)
	{	
		if (game->map_pos[game->y_pos / 32][(game->x_pos - 15) / 32] != '1')
			game->x_pos -= 5;
	}
	if (key == 65363 || key == 100)
	{
		if (game->map_pos[game->y_pos / 32][(game->x_pos + 5) / 32] != '1')
			game->x_pos += 5;	
		//game->x += 1;
	}
	if (key == 65362 || key == 119)
	{
		if (game->map_pos[(game->y_pos - 15) / 32][(game->x_pos) / 32] != '1')
			game->y_pos -= 5;
	}
	if (key == 65364 || key == 115)
	{	
		if (game->map_pos[(game->y_pos + 5) / 32][(game->x_pos) / 32] != '1')
			game->y_pos += 5;
	}
	printf("X: %d\n", game->x);
	printf("Y: %d\n", game->y);
	draw_map(game);
	ft_draw_player(game, 1);
	ft_draw_big_map(game);
	return (0);
}

int	mouse_hook(t_map *game)
{
	(void)game;
	exit(0);
	return (0);
}
