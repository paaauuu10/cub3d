/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 12:11:35 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_buffer_clean(t_map *game, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			game->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	ft_draw_back(int width, int height, t_map *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y < (height >> 1))
				color = game->ceil;
			else
				color = game->floor;
			ft_put_color_to_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
}

void	ft_draw_buffer(int width, int height, t_map *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	ft_draw_back(width, height, game);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			color = game->buffer[y][x];
			if (color != 0)
				ft_put_color_to_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_buffer_fill(int start, int end, t_map *game, int x)
{
	int	color;
	int	j;

	j = start;
	game->tex.num = game->hit_dir;
	while (j < end)
	{
		game->tex.y = (int)game->tex.pos & (TEXHEIGHT - 1);
		game->tex.pos += game->tex.step;
		game->tex.x = (int)(game->tex.wall_x * (double)TEXWIDTH);
		color = ft_get_pixel(game->texture[game->tex.num], \
		game->tex.x, game->tex.y);
		if (color < 0)
			color = -color;
		if (game->side == 1)
			color = (color >> 1) & 8355711;
		game->buffer[j][x] = color;
		j++;
	}
}
