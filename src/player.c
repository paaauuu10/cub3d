/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:23:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/09/06 12:34:06 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
	while (i < size)
	{
		j = 0;
		while(j < size)
        {
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        	j++;
		}
   		i++;
   	}

}

void	ft_draw_player(t_map *game, int flag)
{
	if (flag == 1)
		draw_square(game->mlx_p, game->win_p, game->x_posl, game->y_posl, 9, 0xFFFFFF);
	draw_square(game->mlx_p, game->win_p, game->x_pos, game->y_pos, 9, 0xFF0000);
	game->x_posl = game->x_pos;
	game->y_posl = game->y_pos;
}
	
