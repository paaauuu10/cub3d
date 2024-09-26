/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:23:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/09/06 14:40:49 by pbotargu         ###   ########.fr       */
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
	
	int	x = 9;
	int i = 9;
	void	*img;
	img = mlx_xpm_file_to_image(game->mlx_p, "./Textures/player.xpm", &x, &i);
	if (!img)
		printf("Error\n");
	game->x_pos = game->posX * 32 + 10;
	game->y_pos = game->posY * 32 + 10;
	/*if (flag == 1)
		draw_square(game->mlx_p, game->win_p, game->y_posl, game->x_posl, 9, 0xFFFFFF);
	draw_square(game->mlx_p, game->win_p, game->y_pos, game->x_pos, 9, 0xFF0000);*/
	
	mlx_put_image_to_window(game->mlx_p, game->win_p, img, game->y_pos, game->x_pos);
	game->x_posl = game->x_pos;
	game->y_posl = game->y_pos;
}
	
