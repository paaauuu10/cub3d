/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:45:52 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 09:22:37 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_start_x(t_map *game)
{
	if (game->width <= MINIMAP_SIZE)
		return (0);
	if (game->posx < (MINIMAP_SIZE >> 1))
		return (0);
	else if (game->posx + (MINIMAP_SIZE >> 1) > game->width)
		return (game->width - MINIMAP_SIZE);
	return (game->posx - (MINIMAP_SIZE >> 1));
}

int	calculate_start_y(t_map *game)
{
	if (game->height <= MINIMAP_SIZE)
		return (0);
	if (game->posy < (MINIMAP_SIZE >> 1))
		return (0);
	else if (game->posy + (MINIMAP_SIZE >> 1) > game->height)
		return (game->height - MINIMAP_SIZE);
	return (game->posy - (MINIMAP_SIZE >> 1));
}
