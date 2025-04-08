/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 09:33:05 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_orient_aux(t_map *game)
{
	if (game->per == 'E')
	{
		game->diry = 0;
		game->dirx = 1;
		game->planex = 0;
		game->planey = 0.80;
	}
	else if (game->per == 'W')
	{
		game->diry = 0;
		game->dirx = -1;
		game->planex = 0;
		game->planey = -0.80;
	}
}

void	ft_orientation(t_map *game)
{
	if (game->per == 'N')
	{
		game->diry = -1;
		game->dirx = 0;
		game->planex = 0.80;
		game->planey = 0;
	}
	else if (game->per == 'S')
	{
		game->diry = 1;
		game->dirx = 0;
		game->planex = -0.80;
		game->planey = 0;
	}
	else
		ft_orient_aux(game);
}

void	ft_search_orientation(t_map *game)
{
	if (game->side == 0)
	{
		if (game->stepx > 0)
			game->hit_dir = E;
		else
			game->hit_dir = W;
	}
	else
	{
		if (game->stepy > 0)
			game->hit_dir = S;
		else
			game->hit_dir = N;
	}
}

void	ft_calc_text(t_texture *t, t_map *game, int line_heigth, int start)
{
	t->num = game->r_map[game->mapy][game->mapx] - 1;
	if (game->side == 0)
		t->wall_x = game->posy + game->perpwalldist * game->raydiry;
	else
		t->wall_x = game->posx + game->perpwalldist * game->raydirx;
	t->wall_x -= floor(t->wall_x);
	t->x = (int)(t->wall_x * (double)TEXWIDTH);
	if (game->side == 0 && game->raydirx > 0)
		t->x = TEXWIDTH - t->x - 1;
	if (game->side == 1 && game->raydiry < 0)
		t->x = TEXWIDTH - t->x - 1;
	t->step = 1.0 * TEXHEIGHT / line_heigth;
	t->pos = (start - (SCREENHEIGHT >> 1) + (line_heigth >> 1)) * t->step;
}

void	ft_start_end(t_map *game, int x)
{
	int	line_heigth;
	int	draw_start;
	int	draw_end;

	line_heigth = (int)(SCREENHEIGHT / game->perpwalldist);
	draw_start = (-line_heigth >> 1) + (SCREENHEIGHT >> 1);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_heigth >> 1) + (SCREENHEIGHT >> 1);
	if (draw_end >= SCREENHEIGHT)
		draw_end = SCREENHEIGHT - 1;
	ft_calc_text(&game->tex, game, line_heigth, draw_start);
	ft_buffer_fill(draw_start, draw_end, game, x);
}
