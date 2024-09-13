/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/06 14:54:35 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/09/13 12:40:36 by pborrull         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(void *mlx_ptr, void *win_ptr, int x, int y)
{
	int	i;
	int	j;
	int	size;

	size = 9;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_map *game, int flag)
{
	int	mx;
	int	my;

	if (game->width > MINIMAP_SIZE)
		mx = (game->x_pos -(game->start_x * TILE_SIZE)) + MINIMAP_OFFSET_X - 10;
	else
		mx = game->x_pos + MINIMAP_OFFSET_X - 10;
	if (game->height > MINIMAP_SIZE)
		my = (game->y_pos -(game->start_y * TILE_SIZE)) + MINIMAP_OFFSET_Y - 10;
	else
		my = game->y_pos + MINIMAP_OFFSET_Y - 10;
	draw_square(game->mlx_p, game->win_p, mx, my);
	game->x_posl = mx;
	game->y_posl = my;
	flag = 0;
}
