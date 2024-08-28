/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/26 12:47:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	deal_key(int key, t_map *game)
{
	int	x;
	int	y;

	x = game->x;
	y = game->y;
	if (key == 65307)
	{
		printf("Why are you scared?\n");
		exit(0);
		return (0);
	}
	if (key == 65361 || key == 97)
	{
		mlx_pixel_put(game->mlx_p, game->win_p, x - 10, y, 0xFFFFFF);
		game->x -= 10;
	}
	if (key == 65363 || key == 100)
	{
		mlx_pixel_put(game->mlx_p, game->win_p, x + 10, y, 0xFFFFFF);
		game->x += 10;
	}
	if (key == 65362 || key == 119)
	{
		mlx_pixel_put(game->mlx_p, game->win_p, x, y - 10, 0xFFFFFF);
		game->y -= 10;
	}
	if (key == 65364 || key == 115)
	{
		mlx_pixel_put(game->mlx_p, game->win_p, x, y + 10, 0xFFFFFF);
		game->y += 10;
	}
	return (0);
}

int	mouse_hook(t_map *game)
{
	(void)game;
	exit(0);
	return (0);
}
