/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:46:24 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/06 12:50:48 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_key(int keycode, t_map *game)
{
	double moveSpeed = 0.17;  // Velocidad de movimiento
	double rotSpeed = 0.17;   // Velocidad de rotación

	// Movimiento hacia adelante (tecla W)
	if (keycode == 119)  // 13 es el código de la tecla W en MinilibX
	{
		if (game->r_map[(int)(game->posY + game->dirY * moveSpeed)][(int)(game->posX )] != '1')
			game->posY += game->dirY * moveSpeed;
		if (game->r_map[(int)(game->posY)][(int)(game->posX  + game->dirX * moveSpeed)] != '1')
			game->posX += game->dirX * moveSpeed;
	}
	// Movimiento hacia atrás (tecla S)
	else if (keycode == 115)  // 1 es el código de la tecla S
	{
		if (game->r_map[(int)(game->posY - game->dirY * moveSpeed)][(int)(game->posX )] != '1')
			game->posY -= game->dirY * moveSpeed;
		if (game->r_map[(int)(game->posY)][(int)(game->posX  - game->dirX * moveSpeed)] != '1')
			game->posX -= game->dirX * moveSpeed;
	}
	// Movimiento hacia derecha (tecla D)
	else if (keycode == 100)
	{
		if (game->r_map[(int)(game->posY + game->planeY * moveSpeed)][(int)(game->posX)] != '1')
			game->posY += game->planeY * moveSpeed;
		if (game->r_map[(int)(game->posY)][(int)(game->posX  + game->planeX * moveSpeed)] != '1')
			game->posX += game->planeX * moveSpeed;
	}
	// Movimiento hacia izq (tecla A)
	else if (keycode == 97) 
	{
		if (game->r_map[(int)(game->posY - game->planeY * moveSpeed)][(int)(game->posX)] != '1')
			game->posY -= game->planeY * moveSpeed;
		if (game->r_map[(int)(game->posY)][(int)(game->posX  - game->planeX * moveSpeed)] != '1')
			game->posX -= game->planeX * moveSpeed;
	}
	// Rotar a la derecha (tecla ->)
	else if (keycode == 65361)  
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
		game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
		game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
	}
	// Rotar a la izquierda (tecla <-)
	else if (keycode == 65363)
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
		game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
		game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
	}
	// Cerrar la ventana con tecla ESC
	else if (keycode == 65307)  // 53 es el código de la tecla ESC en MinilibX
		ft_exit(game, "No puede ser que quieras dejar de jugar");
	//mlx_clear_window(game->mlx_p, game->win_p);
	ft_draw_cub(game);
	draw_map(game);
	ft_draw_lines(game);
	ft_draw_player(game, 1);
	return 0;
}
