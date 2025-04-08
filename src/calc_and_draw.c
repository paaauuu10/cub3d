/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_and_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 12:11:15 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_ray_pos_dir(t_map *game, int x)
{
	game->camerax = 2 * x / (double)SCREENWIDTH - 1;
	game->raydirx = game->dirx + game->planex * game->camerax;
	game->raydiry = game->diry + game->planey * game->camerax;
	game->mapx = (int)game->posx;
	game->mapy = (int)game->posy;
	game->sidedistx = 0;
	game->sidedisty = 0;
	if (game->raydirx == 0)
		game->deltadistx = 1e30;
	else
		game->deltadistx = fabs(1 / game->raydirx);
	if (game->raydiry == 0)
		game->deltadisty = 1e30;
	else
		game->deltadisty = fabs(1 / game->raydiry);
	game->perpwalldist = 0;
	game->stepx = 0;
	game->stepy = 0;
	game->hit = 0;
	game->side = 0;
}

void	ft_ray_sidedists(t_map *game)
{
	if (game->raydirx < 0)
	{
		game->stepx = -1;
		game->sidedistx = (game->posx - game->mapx) * game->deltadistx;
	}
	else
	{
		game->stepx = 1;
		game->sidedistx = (game->mapx + 1 - game->posx) * game->deltadistx;
	}
	if (game->raydiry < 0)
	{
		game->stepy = -1;
		game->sidedisty = (game->posy - game->mapy) * game->deltadisty;
	}
	else
	{
		game->stepy = 1;
		game->sidedisty = (game->mapy + 1 - game->posy) * game->deltadisty;
	}
}

void	ft_ray_dda(t_map *game, char **map)
{
	while (game->hit == 0)
	{
		if (game->sidedistx < game->sidedisty)
		{
			game->sidedistx += game->deltadistx;
			game->mapx += game->stepx;
			game->side = 0;
		}
		else
		{
			game->sidedisty += game->deltadisty;
			game->mapy += game->stepy;
			game->side = 1;
		}
		if (map[game->mapy][game->mapx] == '1')
		{
			game->hit = 1;
			ft_search_orientation(game);
		}
	}
	if (game->side == 0)
		game->perpwalldist = game->sidedistx - game->deltadistx;
	else
		game->perpwalldist = game->sidedisty - game->deltadisty;
}

int	ft_draw_cub(t_map *game)
{
	int	x;
	int	w;
	int	h;

	w = SCREENWIDTH;
	h = SCREENHEIGHT;
	x = 0;
	while (x < SCREENWIDTH)
	{
		ft_calc_ray_pos_dir(game, x);
		ft_ray_sidedists(game);
		ft_ray_dda(game, game->r_map);
		ft_start_end(game, x);
		x++;
	}
	ft_draw_buffer(SCREENWIDTH, SCREENHEIGHT, game);
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
	ft_buffer_clean(game, SCREENWIDTH, SCREENHEIGHT);
	return (0);
}
