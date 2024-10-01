/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:29:47 by pbotargu          #+#    #+#             */
/*   Updated: 2024/10/01 10:33:00 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_first_image(t_map *game)
{
	int		width;
	int		height;

	width = 1280;
	height = 960;
	game->im = mlx_xpm_file_to_image(game->mlx_p, "./Textures/portada.xpm", \
	&width, &height);
	if (!game->im)
		ft_exit(game, "Uploading screen information");
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->im, 0, 0);
}

void	ft_upload_texture(t_map *game, int i)
{
	if (i == 0)
		game->texture[0]->t = ft_strdup(game->n_wall);
	if (i == 1)
		game->texture[1]->t = ft_strdup(game->s_wall);
	if (i == 2)
		game->texture[2]->t = ft_strdup(game->w_wall);
	if (i == 3)
		game->texture[3]->t = ft_strdup(game->e_wall);
}

void	ft_init_textures(t_map *game)
{
	int		i;
	int		w;
	int		h;

	i = 0;
	w = 64;
	h = 64;
	while (i < 4)
	{
		game->texture[i] = malloc(sizeof(t_image));
		if (!game->texture[i])
			ft_exit(game, "P*** is forbidden.");
		ft_upload_texture(game, i);
		game->texture[i]->imag = mlx_xpm_file_to_image(game->mlx_p, \
		game->texture[i]->t, &w, &h);
		if (!game->texture[i]->imag)
			ft_exit(game, "Error uploading textures");
		game->texture[i]->addr = mlx_get_data_addr(game->texture[i]->imag, \
		&game->texture[i]->bpp, &game->texture[i]->size_l, \
		&game->texture[i]->endian);
		i++;
	}
}
