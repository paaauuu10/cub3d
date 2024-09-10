/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:34:01 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/10 15:01:24 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lines(t_map *game)
{
	int	width; 
	int	height;
	width = game->width * 32;
	height = game->height * 32;
	if (game->width >= 6)
		width = 32 * 6;
	if (game->height >= 6)
		height = 32 * 6;
	int i = 10;
	int j = 10;
	printf("%d\n", game->width);
	printf("%d\n", game->height);
	while (i <= width + 10)
	{
		j = 10;
		while (j <= height + 10)
		{	
			mlx_pixel_put(game->mlx_p, game->win_p, i, j, 0x000000);
			j++;
		}
		i += 32;
	}
	j = 10;
	while (j <= height + 10)
	{
		i = 10;
		while (i <= width + 10)
		{	
			mlx_pixel_put(game->mlx_p, game->win_p, i, j, 0x000000);
			i++;
		}
		j += 32;
	}
}

void	ft_draw_big_map(t_map *game)
{
	draw_lines(game);
	//draw_blocks(game);
}
