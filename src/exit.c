/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:53:23 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/27 12:19:35 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_exit(t_map *game, char *s)
{
	int	line;

	line = 0;
	if (game->win_p)
		mlx_destroy_window(game->mlx_p, game->win_p);
	if (game->mlx_p)
		free(game->mlx_p);
	while (game->map && game->map[line])
		free(game->map[line++]);
	if (game->map)
		free(game->map);
	game->map = NULL;
	line = 0;
	if (s)
		printf("Error\n%s\n", s);
	exit(1);
}
