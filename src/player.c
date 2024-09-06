/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:23:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/09/05 11:53:17 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        }
    }
}

void	ft_draw_player(t_map *game)
{
	draw_square(game->mlx_p, game->win_p, game->current_x, game->current_y, 8, 0xFF0000);	
}
	
