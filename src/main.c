#include "cub3d.h"
#include <sys/time.h> // Para medir el tiempo

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

void createImage(t_map *game)
{
    game->img_p = mlx_new_image(game->mlx_p, mapWidth, mapHeight);
    game->img_data = mlx_get_data_addr(game->img_p, &game->bpp, &game->size_line, &game->endian);
}

void drawVerticalLine(t_map *game, int x, int startY, int endY, t_ColorRGB color)
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

t_ColorRGB divideColorBy(t_ColorRGB color, int divisor)
{
    t_ColorRGB result;
    result.r = color.r / divisor;
    result.g = color.g / divisor;
    result.b = color.b / divisor;
    return result;
}

void	hit_loop(t_map	*game)
{
	while (game->hit == 0)
    {
       	if (game->sideDistX < game->sideDistY)
       	{
          	game->sideDistX += game->deltaDistX;
           	game->mapX += game->stepX;
           	game->side = 0;
       	}
       	else
       	{
           	game->sideDistY += game->deltaDistY;
           	game->mapY += game->stepY; // Cambiado de stepX a stepY
           	game->side = 1;
       	}
       	if (worldMap[game->mapX][game->mapY] > 0)
           	game->hit = 1;
   	}
}

void	mlx_work_exec(t_map	*game)
{
		printf("dir X%f\n", game->dirX);
        printf("%f\n", game->posX);
        printf("pos Y%f\n", game->posY);
		mlx_hook(game->win_p, 17, 0, mouse_hook, (void *)&game);
		mlx_hook(game->win_p, 2, 1L<<0, handle_key, game);
		mlx_loop(game->mlx_p);
}

void init_game_data(t_map *game, int x)
{
	game->cameraX = 2 * (double)x / (double)screenWidth - 1; //x-coordinate in camera space
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)game->posX;
	game->mapY = (int)game->posY;
	game->deltaDistX = (game->rayDirX == 0) ? 1e30 : fabs(1 / game->rayDirX);
	game->deltaDistY = (game->rayDirY == 0) ? 1e30 : fabs(1 / game->rayDirY);
	game->hit = 0;
}
void	ft_switch(t_map	*game)
{
	switch (worldMap[game->mapX][game->mapY])
	{
		case 1:
			game->color = RGB_Red;
			break;
		case 2:
			game->color = RGB_Green;
			break;
		case 3:
			game->color = RGB_Blue;
			break;
		case 4:
			game->color = RGB_White;
			break;
		default:
			game->color = RGB_Yellow;
			break;
	}
	//revisar si aixo es valid
}

void	ft_time_and_vel(t_map *game)
{
	// Actualizar el tiempo y calcular el frameTime
	game->oldTime = game->time;
	game->time = getTicks();
	game->frameTime = (game->time - game->oldTime) / 1000.0; // frameTime en segundos
   	// Imprimir los FPS
	printFPS(game->frameTime);
   	// Modificadores de velocidad
	game->moveSpeed = game->frameTime * 5.0; // Velocidad de movimiento en cuadrados/segundo
	game->rotSpeed = game->frameTime * 3.0;  // Velocidad de rotación en radianes/segundo
}

void	ft_drawStart_drawEnd(t_map *game)
{
	game->lineHeight = (int)(screenHeight / game->perpWallDist);
	game->drawStart = -game->lineHeight / 2 + screenHeight / 2;
	if (game->drawStart < 0)
		game->drawStart = 0;
	game->drawEnd = game->lineHeight / 2 + screenHeight / 2;
	if (game->drawEnd >= screenHeight)
		game->drawEnd = screenHeight - 1;	
}
void	ft_if_case(t_map *game)
{
	if (game->rayDirX < 0)
	{
		game->stepX = -1;
		game->sideDistX = (game->posX - game->mapX) * game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = (game->mapX + 1.0 - game->posX) * game->deltaDistX;
	}
	if (game->rayDirY < 0)
	{
		game->stepY = -1;
		game->sideDistY = (game->posY - game->mapY) * game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->mapY + 1.0 - game-> posY) * game->deltaDistY;
	}
}

void	game_loop(t_map	*game)
{
	int x;
	
	x = 0;
	/*while (42)
	{*/
		while (x < screenWidth)
    	{
        	init_game_data(game, x);
        	ft_if_case(game);
			hit_loop(game);
        	if (game->side == 0)
            	game->perpWallDist = (game->sideDistX - game->deltaDistX);
        	else
            	game->perpWallDist = (game->sideDistY - game->deltaDistY);
			ft_drawStart_drawEnd(game);
			ft_switch(game);
			if (game->side == 1)
            	game->color = divideColorBy(game->color, 2);
        	drawVerticalLine(game, x, game->drawStart, game->drawEnd, game->color);
			x++;
			ft_time_and_vel(game);
		}
    	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0); // Mostrar la imagen en la ventana
    	mlx_work_exec(game);
	//}
}

int	main(int argc, char **argv)
{
	t_map	game;

	(void)argc;
	ft_bzero(&game, sizeof(t_map));
	map_reading(&game, argv);
	parser(&game);
	int i = 0;
	int j = 0;
	game.oldTime = getTicks();
// x and y player's start position;
	printf("%d\n", game.start_x);
	printf("%d\n", game.start_y);
	game.posX = 4;
	game.posY = 2;
//initial direction vector;
	game.dirX = -1;
	game.dirY = 0;
//the 2d raycaster version of camera plane
	game.planeX = 0;
	game.planeY = 0.66;
	printf("%d\n", game.width);
	printf("%d\n", game.height);
	printf("game_map_pos %c\n", game.map_pos[4][7]);
	game.r_map = (int	**)malloc(game.height * sizeof(int *));
	if (game.r_map == NULL)
		printf("Null game.r_map\n");
	i = 0;
	while(i < game.height)
	{
		game.r_map[i] = (int *)malloc(game.width * sizeof(int) + 1);
		if (game.r_map[i] == NULL)
			printf("game.r_map[i] == NULL\n");
		game.r_map[i][0] = 1;
		i++;
	}
	printf("game.x %d\n", game.x);
	i = game.map_coor;
	j = 0;
	int p = 0;

	while (i < game.height + game.map_coor)
	{
		while(game.map[i][j] != 10)
		{
			//printf("%c", game.map[i][j]);
			game.r_map[p][j] = (int)game.map[i][j];
			//printf("%c", game.r_map[p][j]);
			j++;
		}
		printf("\n");
		i++;
		p++;
		j = 0;
	}

	i = 0;
	j = 0;
	printf("asdasaasa %d\n", game.r_map[i][j]);
	/*while (i <= game.height)
	{
		while (j <= game.width)
		{
			//printf("i %d\n", i);
			printf("j %d\n", j++);
			//printf("%d", game.r_map[i][j++]);
		}
		printf("\n");
		i++;
		j = 0;
	}*/
	game.mlx_p = mlx_init();
	game.win_p = mlx_new_window(game.mlx_p, screenWidth, screenHeight, "cub3d");
	createImage(&game); // Crear la imagen en memoria
	game_loop(&game);
	return (0);
}
