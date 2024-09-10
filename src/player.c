/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:54:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/10 14:58:14 by pborrull         ###   ########.fr       */
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
/*
void	ft_draw_player(t_map *game, int flag)
{
	if (flag == 1)
		draw_square(game->mlx_p, game->win_p, game->x_posl, game->y_posl, 9, 0xFFFFFF);
	draw_square(game->mlx_p, game->win_p, game->x_pos, game->y_pos, 9, 0xFF0000);
	game->x_posl = game->x_pos;
	game->y_posl = game->y_pos;
}*/
void	ft_draw_player(t_map *game, int flag)
{
    int	minimap_x;
	int	minimap_y;

    if (game->width > MINIMAP_SIZE)
		minimap_x = (game->x_pos - (game->start_x * TILE_SIZE)) + MINIMAP_OFFSET_X - 10;
    else
        minimap_x = game->x_pos + MINIMAP_OFFSET_X - 10;
    if (game->height > MINIMAP_SIZE)
		minimap_y = (game->y_pos - (game->start_y * TILE_SIZE)) + MINIMAP_OFFSET_Y - 10;
	else
        minimap_y = game->y_pos + MINIMAP_OFFSET_Y - 10;
    draw_square(game->mlx_p, game->win_p, minimap_x, minimap_y, 9, 0xFF0000);
    game->x_posl = minimap_x;
    game->y_posl = minimap_y;
	flag = 0;
}
