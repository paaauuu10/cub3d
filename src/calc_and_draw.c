/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_and_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 14:14:56 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_ray_pos_dir(t_map *game, int x)
{
	game->cameraX = 2 * x / (double)screenWidth - 1;
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)game->posX;
	game->mapY = (int)game->posY;
	game->sideDistX = 0;
	game->sideDistY = 0;
	if (game->rayDirX == 0)
		game->deltaDistX = 1e30;
	else
		game->deltaDistX = fabs(1 / game->rayDirX);
	if (game->rayDirY == 0)
		game->deltaDistY = 1e30;
	else
		game->deltaDistY = fabs(1 / game->rayDirY);
	game->perpWallDist = 0;
	game->stepX = 0;
	game->stepY = 0;
	game->hit = 0;
	game->side = 0;
}

void	ft_ray_sidedists(t_map *game)
{
	if (game->rayDirX < 0)
	{
		game->stepX = -1;
		game->sideDistX = (game->posX - game->mapX) * game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = (game->mapX + 1 - game->posX) * game->deltaDistX;
	}
	if (game->rayDirY < 0)
	{
		game->stepY = -1;
		game->sideDistY = (game->posY - game->mapY) * game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->mapY + 1 - game->posY) * game->deltaDistY;
	}
}

void	ft_ray_dda(t_map *game, char **map)
{
	while (game->hit == 0)
	{
		if (game->sideDistX < game->sideDistY)
		{
			game->sideDistX += game->deltaDistX;
			game->mapX += game->stepX;
			game->side = 0;
		}
		else
		{
			game->sideDistY += game->deltaDistY;
			game->mapY += game->stepY;
			game->side = 1;
		}
		if (map[game->mapY][game->mapX] == '1')
		{
			game->hit = 1;
			ft_search_orientation(game);
		}
	}
	if (game->side == 0)
		game->perpWallDist = game->sideDistX - game->deltaDistX;
	else
		game->perpWallDist = game->sideDistY - game->deltaDistY;
}

int	ft_draw_cub(t_map *game)
{
	int	x;
	int	w;
	int	h;

	w = screenWidth;
	h = screenHeight;
	x = 0;
	while (x < screenWidth)
	{
		ft_calc_ray_pos_dir(game, x);
		ft_ray_sidedists(game);
		ft_ray_dda(game, game->r_map);
		ft_start_end(game, x);
		x++;
	}
	ft_draw_buffer(screenWidth, screenHeight, game);
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
	ft_buffer_clean(game, screenWidth, screenHeight);
	return (0);
}
