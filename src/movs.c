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

int	deal_key(int key, t_map *game)
{
	double moveSpeed = 0.05;  // Velocidad de movimiento
    double rotSpeed = 0.05;   // Velocidad de rotación
    printf("%f\n", game->dirX);
    printf("%f\n", game->dirY);
    printf("%d\n", (int)game->posY);
    printf("%d\n", (int)game->posX);
    printf("%d\n", game->y_pos);
    printf("%d\n", game->x_pos);
    printf("test: %d\n",(int)(game->posX + game->dirX * moveSpeed));
    //printf("test char: %c\n", game->map_pos[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)]);
    int i =0;
    int j = 0;
    while (game->map_pos[i][j])
    {
        while(game->map_pos[i][j])
            printf("%c", game->map_pos[i][j++]);
        i++;
        j = 0;
    }
    if (key == 65307)
		ft_exit(game, "Why are you scared?");
    // Movimiento hacia adelante (tecla W)
    if (key == 119)  // 13 es el código de la tecla W en MinilibX
    {
        if (game->map_pos[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)] != '1')
            game->posX += game->dirX * moveSpeed;
        if (game->map_pos[(int)(game->posX)][(int)(game->posY + game->dirY * moveSpeed)] != '1')
            game->posY += game->dirY * moveSpeed;
    }




    if (key == 65361 || key == 97)
	{	
		if (game->map_pos[game->y_pos / 32][(game->x_pos - 15) / 32] != '1')
			game->x_pos -= 5;
	}
	if (key == 65363 || key == 100)
	{
		if (game->map_pos[game->y_pos / 32][(game->x_pos + 5) / 32] != '1')
			game->x_pos += 5;	
	}
	if (key == 65362 || key == 119)
	{
		if (game->map_pos[(game->y_pos - 15) / 32][(game->x_pos) / 32] != '1')
			game->y_pos -= 5;
	}
	if (key == 65364 || key == 115)
	{	
		if (game->map_pos[(game->y_pos + 5) / 32][(game->x_pos) / 32] != '1')
			game->y_pos += 5;
	}
	draw_map(game);
	ft_draw_player(game, 1);
	ft_draw_big_map(game);
	return (0);
}

int handle_key(int keycode, t_map *game)
{
    double moveSpeed = 0.05;  // Velocidad de movimiento
    double rotSpeed = 0.05;   // Velocidad de rotación


    // Movimiento hacia adelante (tecla W)
    if (keycode == 119)  // 13 es el código de la tecla W en MinilibX
    {
        if (game->map_pos[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)] != 1)
            game->posX += game->dirX * moveSpeed;
        if (game->map_pos[(int)(game->posX)][(int)(game->posY + game->dirY * moveSpeed)] != 1)
            game->posY += game->dirY * moveSpeed;
    }
    // Movimiento hacia atrás (tecla S)
    if (keycode == 115)  // 1 es el código de la tecla S
    {
        if (game->map_pos[(int)(game->posX - game->dirX * moveSpeed)][(int)(game->posY)] == 0)
            game->posX -= game->dirX * moveSpeed;
        if (game->map_pos[(int)(game->posX)][(int)(game->posY - game->dirY * moveSpeed)] == 0)
            game->posY -= game->dirY * moveSpeed;
    }
    // Rotar a la derecha (tecla D)
    if (keycode == 100)  // 2 es el código de la tecla D
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    // Rotar a la izquierda (tecla A)
    if (keycode == 97)  // 0 es el código de la tecla A
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
    // Cerrar la ventana con tecla ESC
    if (keycode == 65307)  // 53 es el código de la tecla ESC en MinilibX
        mlx_destroy_window(game->mlx_p, game->win_p);

    return 0;
}

/*int handle_key(int keycode, t_map *game)
{
    double moveSpeed = 0.05;  // Velocidad de movimiento
    double rotSpeed = 0.05;   // Velocidad de rotación

    // Movimiento hacia adelante (tecla W)
    if (keycode == UP_KEY)
    {
        int newPosX = (int)(game->posX + game->dirX * moveSpeed);
        int newPosY = (int)(game->posY + game->dirY * moveSpeed);

        // Verificar que no hay una pared en la nueva posición
        if (game->map_real[newPosX][(int)(game->posY)] == 0)
            game->posX += game->dirX * moveSpeed;
        if (game->map_real[(int)(game->posX)][newPosY] == 0)
            game->posY += game->dirY * moveSpeed;
    }

    // Movimiento hacia atrás (tecla S)
    if (keycode == DOWN_KEY)
    {
        int newPosX = (int)(game->posX - game->dirX * moveSpeed);
        int newPosY = (int)(game->posY - game->dirY * moveSpeed);

        if (game->map_real[newPosX][(int)(game->posY)] == 0)
            game->posX -= game->dirX * moveSpeed;
        if (game->map_real[(int)(game->posX)][newPosY] == 0)
            game->posY -= game->dirY * moveSpeed;
    }

    // Rotar a la derecha (tecla D)
    if (keycode == RIGHT_KEY)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);

        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }

    // Rotar a la izquierda (tecla A)
    if (keycode == LEFT_KEY)
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);

        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }

    // Cerrar el juego con la tecla ESC
    if (keycode == ESC_KEY)
        mlx_destroy_window(game->mlx_p, game->win_p);

    return (0);
}*/

// Esta función se llamará cada vez que se presione una tecla
int	mouse_hook(t_map *game)
{
	(void)game;
	exit(0);
	return (0);
}
