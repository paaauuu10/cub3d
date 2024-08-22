/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:30:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/22 09:48:37 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int	add_lines(t_map *game, char *line)
{
	char	**temp;
	int		i;

	i = 0;
	game->height++;
	temp = (char **)malloc((game->height + 1) * sizeof(char *));
	if (!temp)
		ft_exit(game);
	temp[game->height] = NULL;
	while (i < game->height - 1)
	{
		temp[i] = game->map[i];
		i++;
	}
	temp[i] = line;
	if (game->map)
		free(game->map);
	game->map = temp;
	return (1);
}


int	map_reading(t_map *game, char **s)
{
	char	*line;

	game->i = 0;
	game->fd = open (s[1], O_RDONLY);
	if (game->fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		add_lines (game, line);
	}
	close (game->fd);
	if (!game->map)
	{
		ft_printf("Error\nI need a valid map\n");
		ft_exit(game);
	}
	while (game->map[game->i])
		game->width = calc_width(game->map[game->i++], game);
	return (1);
}*/

int	deal_key(int key, t_map *mapa)
{
	int	x;
	int	y;
	
	x = mapa->x;
	y = mapa->y;
	if (key == 65307)
	{
		printf("Why are you scared?\n");
		exit(0);
		return (0);
	}
	if (key == 65361 || key == 97)
//		left(game, key, x, y);
	{
//		printf("left\n");
		mlx_pixel_put(mapa->mlx_p, mapa->win_p, x - 10, y, 0xFFFFFF);
		mapa->x -= 10;
	}
	if (key == 65363 || key == 100)
//		right(game, x, y);
	{
	//	printf("right\n");
		mlx_pixel_put(mapa->mlx_p, mapa->win_p, x + 10, y, 0xFFFFFF);
		mapa->x += 10;
	}
	if (key == 65362 || key == 119)
//		up(game, x, y);	
	{
	//	printf("up\n");
		mlx_pixel_put(mapa->mlx_p, mapa->win_p, x, y - 10, 0xFFFFFF);
		mapa->y -= 10;
	}
	if (key == 65364 || key == 115)
//		down(game, key, x, y);
	{
	//	printf("down\n");
		mlx_pixel_put(mapa->mlx_p, mapa->win_p, x, y + 10, 0xFFFFFF);
		mapa->y += 10;
	}
	return (0);
}

int	mouse_hook(t_map *game)
{
	exit(0);
	return (0);
}


int	main(int argc, char **argv)
{
	t_map	mapa;

	mapa.x = 1000;
	mapa.y = 500;
	mapa.win_p = NULL;
	mapa.mlx_p = NULL;	
	mapa.mlx_p = mlx_init();
	mapa.win_p = mlx_new_window(mapa.mlx_p, 2048, 1024, "cub3d");
	mlx_pixel_put(mapa.mlx_p, mapa.win_p, 1024, 512, 0xFFFFFF);
	mlx_key_hook(mapa.win_p, deal_key, (void *)&mapa);
	mlx_hook(mapa.win_p, 17, 0, mouse_hook, (void *)&mapa);
	mlx_loop(mapa.mlx_p);
	return (0);	
}
