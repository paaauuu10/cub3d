/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:28:12 by pbotargu          #+#    #+#             */
/*   Updated: 2024/09/05 13:13:10 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lines(t_map *game)
{
	int	witdh = game->width * 12;
	int	height = game->height * 24;

	int i = 0;
	int j = 0;
	printf("%d\n", game->width);
	printf("%d\n", game->height);
	while (i <= witdh)
	{
		j = 0;
		while (j <= height)
		{	
			mlx_pixel_put(game->mlx_p, game->win_p, i, j, 0xFFFFFF);
			j++;
		}
		i += 60;
	}
	j = 0;
	while (j <= height)
	{
		i = 0;
		while (i <= witdh)
		{	
			mlx_pixel_put(game->mlx_p, game->win_p, i, j, 0xFFFFFF);
			i++;
		}
		j += 60;
	}
}

void	ft_draw_big_map(t_map *game)
{
	draw_lines(game);
}
