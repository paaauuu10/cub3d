/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pborrull <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/26 12:46:24 by pborrull		  #+#	#+#			 */
/*   Updated: 2024/10/01 11:37:52 by pbotargu         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(t_map *game)
{
	printf("No puede ser que quieras dejar de jugar.¡Vuelve aquí!\n");
	ft_exit(game, NULL);
	return (0);
}

int	handle_rotation(int keycode, t_map *game, double rotS)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == 65361 || keycode == 65363)
	{
		olddirx = game->dirx;
		oldplanex = game->planex;
		if (keycode == 65361)
			rotS = -rotS;
		game->dirx = game->dirx * cos(rotS) - game->diry * sin(rotS);
		game->diry = olddirx * sin(rotS) + game->diry * cos(rotS);
		game->planex = game->planex * cos(rotS) - game->planey * sin(rotS);
		game->planey = oldplanex * sin(rotS) + game->planey * cos(rotS);
	}
	return (0);
}

int	handle_movement(int keycode, t_map *g, double moveS)
{
	if (keycode == 119 || keycode == 115)
	{
		if (keycode == 115)
			moveS = -moveS;
		if (g->r_map[(int)(g->posy + (g->diry * moveS))][(int)g->posx] != '1')
			g->posy += g->diry * moveS;
		if (g->r_map[(int)g->posy][(int)(g->posx + (g->dirx * moveS))] != '1')
			g->posx += g->dirx * moveS;
	}
	else if (keycode == 100)
	{
		if (g->r_map[(int)(g->posy + g->planey * moveS)][(int)(g->posx)] != '1')
			g->posy += g->planey * moveS;
		if (g->r_map[(int)(g->posy)][(int)(g->posx + g->planex * moveS)] != '1')
			g->posx += g->planex * moveS;
	}
	else if (keycode == 97)
	{
		if (g->r_map[(int)(g->posy - g->planey * moveS)][(int)(g->posx)] != '1')
			g->posy -= g->planey * moveS;
		if (g->r_map[(int)(g->posy)][(int)(g->posx - g->planex * moveS)] != '1')
			g->posx -= g->planex * moveS;
	}
	return (0);
}

int	handle_key(int keycode, t_map *game)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.17;
	rotspeed = 0.17;
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		handle_movement(keycode, game, movespeed);
	else if (keycode == 65361 || keycode == 65363)
		handle_rotation(keycode, game, rotspeed);
	else if (keycode == 65307)
	{
		printf("No puede ser que quieras dejar de jugar.¡Vuelve aquí!\n");
		ft_exit(game, NULL);
	}
	ft_draw_cub(game);
	draw_map(game);
	ft_draw_lines(game);
	ft_draw_player(game, 1);
	return (0);
}
