/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:30:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/10 15:23:39 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdint.h>
/*int	main(int argc, char **argv)
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
	printf("%d\n", game.width);
	printf("%d\n", game.height);
	game.x_pos = game.x * 32 + 20;
	game.y_pos = game.y * 32 - 10;
	printf("Calculate x: %d\n", game.x_pos);
	draw_map(&game);
	ft_draw_player(&game, 0);
	ft_draw_big_map(&game);
	//mlx_key_hook(game.win_p, deal_key, (void *)&game);
	mlx_hook(game.win_p, 17, 0, mouse_hook, (void *)&game);
	mlx_hook(game.win_p, 2, 1L<<0, deal_key, (void *)&game);
	mlx_loop(game.mlx_p);
	return (0);
}*/

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ColorRGB;

#define RGB_Red   (ColorRGB){255, 0, 0}
#define RGB_Green (ColorRGB){0, 255, 0}
#define RGB_Blue  (ColorRGB){0, 0, 255}
#define RGB_White (ColorRGB){255, 255, 255}
#define RGB_Yellow (ColorRGB){255, 255, 0}

#define mapWidth 2048
#define mapHeight 1024
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//calculate ray position and direction
void	rays(t_map *game, double planeX, double planeY, double dirX, double dirY)
{
	int	x;

	x = 0;
	while (x < mapWidth)
	{
		double cameraX = 2 * (double)x / (double)mapWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		x++;
		printf("CameraX->  %f\n", cameraX);
		printf("RayDirX->  %f\n", rayDirX);
		printf("RayDirY->  %f\n", rayDirY);
		printf("\n\n");
	}
}


void verLine(void *mlx, void *win, int x, int startY, int endY, ColorRGB color)
{
    int y = startY;

    while (y <= endY)
    {
        mlx_pixel_put(mlx, win, x, y, (color.r << 16) | (color.g << 8) | color.b);
        y++;
    }
}

ColorRGB divideColorBy(ColorRGB color, int divisor)
{
    ColorRGB result;
    result.r = color.r / divisor;
    result.g = color.g / divisor;
    result.b = color.b / divisor;
    return result;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_map	game;

	double posX = 22, posY = 12; // x and y player's start position;
	double dirX = -1, dirY = 0; //initial direction vector;
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	game.win_p = NULL;
	game.mlx_p = NULL;
	ft_bzero(&game, sizeof(t_map));
	//map_reading(&game, argv);
	//parser(&game);
	game.mlx_p = mlx_init();
	game.win_p = mlx_new_window(game.mlx_p, 2048, 1024, "cub3d");
	//rays(&game, planeX, planeY, dirX, dirY);
	int	x;

	x = 0;
	while (x < mapWidth)
	{
		double cameraX = 2 * (double)x / (double)mapWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		x++;
		//box of the map were in
		int	mapX = (int)posX;
		int mapY = (int)posY;

		//lenght of the ray from current positions to next x or y-side
		double sideDistX;
		double sideDistY;

		//lenght of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
    	double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int	stepX;
		int	stepY;

		int hit = 0; //was there a wall hit?
		int side;	//was a NS or a EW wall hit?

		//calculate step and initial sideDist
      	if (rayDirX < 0)
      	{
        	stepX = -1;
        	sideDistX = (posX - mapX) * deltaDistX;
     	}
     	else
     	{
       	 	stepX = 1;
       	 	sideDistX = (mapX + 1.0 - posX) * deltaDistX;
     	}
      	if (rayDirY < 0)
      	{
        	stepY = -1;
        	sideDistY = (posY - mapY) * deltaDistY;
      	}
      	else
      	{
       		stepY = 1;
        	sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      	}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, eiter in x-direction, or in y-direction
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepX;
					side = 1;
				}
				//check  if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}

		}
		// calculate distance projected on camera direction (Euclidian distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// calculate height of line to draw on screen
		int	lineHeight = (int)(mapHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int	drawStart = -lineHeight / 2 + mapHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + mapHeight / 2;
		if (drawEnd >= mapHeight)
			drawEnd = mapHeight - 1;

		// choose wall color
		ColorRGB color;
		switch (worldMap[mapX][mapY])
		{
        	case 1:
            	color = RGB_Red;
            	break;
        	case 2:
            	color = RGB_Green;
            	break;
        	case 3:
            	color = RGB_Blue;
            	break;
        	case 4:
            	color = RGB_White;
            	break;
        	default:
            	color = RGB_Yellow;
            	break;
		}
		
		//give x and y sides differents brightness
		if (side == 1)
			color = divideColorBy(color, 2);

		//draw the pixels of the stripe as a vertical line
		verLine(game.mlx_p, game.win_p, x, drawStart, drawEnd, color);
	}
	
	//game.x_pos = game.x * 32 + 20;
	//game.y_pos = game.y * 32 - 10;
	//draw_map(&game);
	//ft_draw_player(&game, 0);
	//ft_draw_big_map(&game);
	//mlx_key_hook(game.win_p, deal_key, (void *)&game);
	mlx_hook(game.win_p, 17, 0, mouse_hook, (void *)&game);
	mlx_hook(game.win_p, 2, 1L<<0, deal_key, (void *)&game);
	mlx_loop(game.mlx_p);
	return (0);

}

