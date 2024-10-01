/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:49:40 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 10:25:04 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>  // Para uint32_t_t
#include <sys/time.h> // Para medir el tiempo

void	ft_create_image(t_map *game)
{
	game->img_p = mlx_new_image(game->mlx_p, SCREENWIDTH, SCREENHEIGHT);
	game->img_data = mlx_get_data_addr(game->img_p, &game->bpp, \
	&game->size_line, &game->endian);
}

void	ft_r_map_aux(t_map *game, int i, int j)
{
	int	p;

	p = 0;
	while (i < game->height + game->map_coor)
	{
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			game->r_map[p][j] = game->map[i][j];
			j++;
		}
		i++;
		p++;
		j = 0;
	}
}

void	ft_create_r_map(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->r_map = (char **)malloc(game->height * sizeof(char *));
	if (game->r_map == NULL)
		ft_exit(game, "Malloc failed");
	i = 0;
	while (i < game->height)
	{
		game->r_map[i] = (char *)malloc(game->width * sizeof(char) + 1);
		if (game->r_map[i] == NULL)
			ft_exit(game, "Malloc failed");
		i++;
	}
	i = game->map_coor;
	j = 0;
	ft_r_map_aux(game, i, j);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = (t_map *)malloc(sizeof(t_map));
	if (argc != 2)
		return (1);
	ft_bzero(game, sizeof(t_map));
	ft_map_reading(game, argv);
	ft_parser(game);
	game->posx = game->x + 0.5;
	game->posy = game->y + 0.5;
	ft_orientation(game);
	ft_create_r_map(game);
	game->mlx_p = mlx_init();
	game->win_p = mlx_new_window(game->mlx_p, SCREENWIDTH, SCREENHEIGHT, \
	"cub3d");
	ft_init_textures(game);
	ft_create_image(game);
	ft_first_image(game);
	mlx_hook(game->win_p, 17, 0, mouse_hook, game);
	mlx_hook(game->win_p, 2, 1L << 0, handle_key, game);
	mlx_loop(game->mlx_p);
	return (0);
}
