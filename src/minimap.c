/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/28 09:51:52 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/09/06 12:45:24 by pbotargu         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0xFFFFFF);
	else
		return (0x60C0C0C0);
}

void	draw_tile(t_map *game, int x, int y, int color)
{
	int	xi;
	int	yi;

	xi = x;
	yi = y;
	while (yi < y + TILE_SIZE)
	{
		xi = x;
		while (xi < x + TILE_SIZE)
		{
			mlx_pixel_put(game->mlx_p, game->win_p, xi, yi, color);
			xi++;
		}
		yi++;
	}
}

int	get_tile_color(t_map *game, int i, int j)
{
	char	tile;
	int		color;

	tile = '1';
	if (j >= 0 && (unsigned long)j < ft_strlen(game->map_pos[i]))
		tile = game->map_pos[i][j];
	color = get_color(tile);
	/*if (game->y == i && game->x == j)
		color = 0xFFFF0000;*/
	return (color);
}

void	ft_draw_map_aux(t_map *game)
{
	int		j;
	int		i;
	char	tile;
	int		color;

	i = game->start_y;
	i = 0;
	while (i < game->start_y + MINIMAP_SIZE && i < game->height)
	{
		game->current_x = MINIMAP_OFFSET_X;
		j = game->start_x;
		while (j < game->start_x + MINIMAP_SIZE && j < game->width)
		{
			tile = '1';
			if (j >= 0 && (unsigned long)j < ft_strlen(game->map_pos[i]))
				tile = game->map_pos[i][j];
			color = get_color(tile);
		/*	if (game->y == i && game->x == j)
				color = 0xFFFF0000;*/
			draw_tile(game, game->current_x, game->current_y, color);
			game->current_x += TILE_SIZE;
			j++;
		}
		game->current_y += TILE_SIZE;
		i++;
	}
}

void	draw_map(t_map *game)
{
	game->start_x = calculate_start_x(game);
	game->start_y = calculate_start_y(game);
	if (game->start_x < 0)
		game->start_x = 0;
	if (game->start_y < 0)
		game->start_y = 0;
	game->current_y = MINIMAP_OFFSET_Y;
	game->current_x = MINIMAP_OFFSET_X;
	ft_draw_map_aux(game);
}
