/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:30:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/10 11:52:39 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	game;

	if (argc != 2)
	{
		printf("Error\nWe need a map to play.\n");
		exit(0);
	}
	game.win_p = NULL;
	game.mlx_p = NULL;
	ft_bzero(&game, sizeof(t_map));
	map_reading(&game, argv);
	parser(&game);
	game.mlx_p = mlx_init();
	game.win_p = mlx_new_window(game.mlx_p, 2048, 1024, "cub3d");
	game.x_pos = game.x * 32 + 22;
	game.y_pos = game.y * 32 + 22;
	printf("Calculate x: %d\n", game.x_pos);
	draw_map(&game);
	ft_draw_player(&game, 0);
	ft_draw_big_map(&game);
	mlx_hook(game.win_p, 17, 0, mouse_hook, (void *)&game);
	mlx_hook(game.win_p, 2, 1L << 0, deal_key, (void *)&game);
	mlx_loop(game.mlx_p);
	return (0);
}
