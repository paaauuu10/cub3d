/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/28 14:14:56 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_pixel(t_image *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->size_l + x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	ft_put_color_to_pixel(t_map *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}
