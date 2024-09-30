/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/30 14:35:06 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_rotation(int keycode, t_map *game, double rotS)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == 65361 || keycode == 65363)
	{
		olddirx = game->dirX;
		oldplanex = game->planeX;
		if (keycode == 65361)
			rotS = -rotS;
		game->dirX = game->dirX * cos(rotS) - game->dirY * sin(rotS);
		game->dirY = olddirx * sin(rotS) + game->dirY * cos(rotS);
		game->planeX = game->planeX * cos(rotS) - game->planeY * sin(rotS);
		game->planeY = oldplanex * sin(rotS) + game->planeY * cos(rotS);
	}
	return (0);
}

int	handle_movement(int keycode, t_map *g, double moveS)
{
	if (keycode == 119 || keycode == 115)
	{
		if (keycode == 115)
			moveS = -moveS;
		if (g->r_map[(int)(g->posY + g->dirY * moveS)][(int)g->posX] != '1')
			g->posY += g->dirY * moveS;
		if (g->r_map[(int)g->posY][(int)(g->posX + g->dirX * moveS)] != '1')
			g->posX += g->dirX * moveS;
	}
	else if (keycode == 97 || keycode == 100)
	{
		if (keycode == 97)
			moveS = -moveS;
		if (g->r_map[(int)(g->posY + g->planeY * moveS)][(int)g->posX] != '1')
			g->posY += g->planeY * moveS;
		if (g->r_map[(int)g->posY][(int)(g->posX + g->planeX * moveS)] != '1')
			g->posX += g->planeX * moveS;
	}
	return (0);
}

int	handle_key(int keycode, t_map *game)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.17;
	rotspeed = 0.17;
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		handle_movement(keycode, game, movespeed);
	else if (keycode == 65361 || keycode == 65363)
		handle_rotation(keycode, game, rotspeed);
	else if (keycode == 65307)
		ft_exit(game, "No puede ser que quieras dejar de jugar");
	ft_draw_cub(game);
	draw_map(game);
	ft_draw_lines(game);
	ft_draw_player(game, 1);
	return (0);
}
