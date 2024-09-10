#include "cub3d.h"
#include <stdint.h> // Para uint8_t
#include <sys/time.h> // Para medir el tiempo

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
#define screenWidth 2048
#define screenHeight 1024

struct timeval oldTime, time;

// Función para obtener el tiempo en milisegundos
double getTicks()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return (currentTime.tv_sec * 1000.0) + (currentTime.tv_usec / 1000.0);
}

// Función para calcular y mostrar los FPS
void printFPS(double frameTime)
{
    if (frameTime > 0)
    {
        double fps = 1.0 / frameTime;
        printf("FPS: %.2f\n", fps);
    }
}

int worldMap[mapWidth][mapHeight]=
{
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,1,1,1,1,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void putImageToWindow(t_map *game)
{
    mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
}

void createImage(t_map *game)
{
    game->img_p = mlx_new_image(game->mlx_p, mapWidth, mapHeight);
    game->img_data = mlx_get_data_addr(game->img_p, &game->bpp, &game->size_line, &game->endian);
}

void drawVerticalLine(t_map *game, int x, int startY, int endY, ColorRGB color)
{
    int y = startY;
    while (y <= endY)
    {
        int pixel = (y * game->size_line) + (x * (game->bpp / 8));
        game->img_data[pixel] = color.b;        // Blue
        game->img_data[pixel + 1] = color.g;    // Green
        game->img_data[pixel + 2] = color.r;    // Red
        game->img_data[pixel + 3] = 0;          // Alpha (transparente en la mayoría de los casos)
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
	
	double oldTime = getTicks();
    double time;
    double frameTime;

    t_map game;
    double posX = 22, posY = 12; // x and y player's start position;
    double dirX = -1, dirY = 0; //initial direction vector;
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    game.mlx_p = mlx_init();
    game.win_p = mlx_new_window(game.mlx_p, screenWidth, screenHeight, "cub3d");

    createImage(&game); // Crear la imagen en memoria

    int x = 0;
    while (42)
	{
		while (x < screenWidth)
    	{
        	double cameraX = 2 * (double)x / (double)screenWidth - 1; //x-coordinate in camera space
        	double rayDirX = dirX + planeX * cameraX;
        	double rayDirY = dirY + planeY * cameraX;

        	int mapX = (int)posX;
        	int mapY = (int)posY;

        	double sideDistX;
       		double sideDistY;
        	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        	double perpWallDist;

        	int stepX;
        	int stepY;

        	int hit = 0;
        	int side;

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

        	while (hit == 0)
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
                	mapY += stepY; // Cambiado de stepX a stepY
                	side = 1;
            	}

            	if (worldMap[mapX][mapY] > 0)
                	hit = 1;
        	}

        	if (side == 0)
            	perpWallDist = (sideDistX - deltaDistX);
        	else
            	perpWallDist = (sideDistY - deltaDistY);

        	int lineHeight = (int)(screenHeight / perpWallDist);

        	int drawStart = -lineHeight / 2 + screenHeight / 2;
        	if (drawStart < 0)
            	drawStart = 0;
        	int drawEnd = lineHeight / 2 + screenHeight / 2;
        	if (drawEnd >= screenHeight)
            	drawEnd = screenHeight - 1;

        	ColorRGB color;
        	switch (worldMap[mapX][mapY])
        	{
            	case 1:
                	color = RGB_Red;
                	break;
            	case 2:
                	color = RGB_Red;
                	break;
           		case 3:
                	color = RGB_Red;
                	break;
            	case 4:
                	color = RGB_Red;
                	break;
            	default:
                	color = RGB_Yellow;
                	break;
        	}

        	if (side == 1)
            	color = divideColorBy(color, 2);

        	drawVerticalLine(&game, x, drawStart, drawEnd, color);
        	
			x++;

			// Actualizar el tiempo y calcular el frameTime
        	oldTime = time;
        	time = getTicks();
        	frameTime = (time - oldTime) / 1000.0; // frameTime en segundos

        	// Imprimir los FPS
        	printFPS(frameTime);

        	// Modificadores de velocidad
        	double moveSpeed = frameTime * 5.0; // Velocidad de movimiento en cuadrados/segundo
        	double rotSpeed = frameTime * 3.0;  // Velocidad de rotación en radianes/segundo
		}
    	putImageToWindow(&game); // Mostrar la imagen en la ventana
    	mlx_hook(game.win_p, 17, 0, mouse_hook, (void *)&game);
		mlx_hook(game.win_p, 2, 1L<<0, deal_key, (void *)&game);
		mlx_loop(game.mlx_p);
	}
	return (0);
}

