/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 14:14:56 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_orient_aux(t_map *game)
{
	if (game->per == 'E')
	{
		game->dirY = 0;
		game->dirX = 1;
		game->planeX = 0;
		game->planeY = 0.80;
	}
	else if (game->per == 'W')
	{
		game->dirY = 0;
		game->dirX = -1;
		game->planeX = 0;
		game->planeY = -0.80;
	}
}

void	ft_orientation(t_map *game)
{
	if (game->per == 'N')
	{
		game->dirY = -1;
		game->dirX = 0;
		game->planeX = 0.80;
		game->planeY = 0;
	}
	else if (game->per == 'S')
	{
		game->dirY = 1;
		game->dirX = 0;
		game->planeX = -0.80;
		game->planeY = 0;
	}
	else
		ft_orient_aux(game);
}

void	ft_search_orientation(t_map *game)
{
	if (game->side == 0)
	{
		if (game->stepX > 0)
			game->hit_dir = E;
		else
			game->hit_dir = W;
	}
	else
	{
		if (game->stepY > 0)
			game->hit_dir = S;
		else
			game->hit_dir = N;
	}
}

void	ft_calc_text(t_texture *t, t_map *game, int line_heigth, int start)
{
	t->num = game->r_map[game->mapY][game->mapX] - 1;
	if (game->side == 0)
		t->wall_x = game->posY + game->perpWallDist * game->rayDirY;
	else
		t->wall_x = game->posX + game->perpWallDist * game->rayDirX;
	t->wall_x -= floor(t->wall_x);
	t->x = (int)(t->wall_x * (double)texWidth);
	if (game->side == 0 && game->rayDirX > 0)
		t->x = texWidth - t->x - 1;
	if (game->side == 1 && game->rayDirY < 0)
		t->x = texWidth - t->x - 1;
	t->step = 1.0 * texHeight / line_heigth;
	t->pos = (start - (screenHeight >> 1) + (line_heigth >> 1)) * t->step;
}

void	ft_start_end(t_map *game, int x)
{
	int	line_heigth;
	int	draw_start;
	int	draw_end;

	line_heigth = (int)(screenHeight / game->perpWallDist);
	draw_start = (-line_heigth >> 1) + (screenHeight >> 1);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_heigth >> 1) + (screenHeight >> 1);
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	ft_calc_text(&game->tex, game, line_heigth, draw_start);
	ft_buffer_fill(draw_start, draw_end, game, x);
}
