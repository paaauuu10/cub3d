/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:45:52 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/29 10:20:20 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_start_x(t_map *game)
{
	if (game->width < MINIMAP_SIZE)
		return (0);
	if (game->x < MINIMAP_SIZE / 2)
		return (0);
	else if (game->x + MINIMAP_SIZE / 2 > game->width)
		return (game->width - MINIMAP_SIZE);
	return (game->x - MINIMAP_SIZE / 2);
}

int	calculate_start_y(t_map *game)
{
	if (game->height < MINIMAP_SIZE)
		return (0);
	if (game->y < MINIMAP_SIZE / 2)
		return (0);
	else if (game->y + MINIMAP_SIZE / 2 > game->height - 6)
		return (game->height - 6 - MINIMAP_SIZE);
	return (game->y - MINIMAP_SIZE / 2);
}
