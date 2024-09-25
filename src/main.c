#include "cub3d.h"
#include <stdint.h>  // Para uint32_t_t
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

void createImage(t_map *game)
{
    if (game->img_p != NULL)
        mlx_destroy_image(game->mlx_p, game->img_p);
	game->img_p = mlx_new_image(game->mlx_p, screenWidth, screenHeight);
    game->img_data = mlx_get_data_addr(game->img_p, &game->bpp, &game->size_line, &game->endian);
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
       	if (game->r_map[game->mapY][game->mapX] == '1')
           	game->hit = 1;
   	}
}

void	mlx_work_exec(t_map	*game)
{
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

void	ft_time_and_vel(t_map *game)
{
	// Actualizar el tiempo y calcular el frameTime
	game->oldTime = game->time;
	game->time = getTicks();
	game->frameTime = (game->time - game->oldTime) / 1000.0; // frameTime en segundos
   	// Imprimir los FPS
	//printFPS(game->frameTime);
   	// Modificadores de velocidad
	game->moveSpeed = game->frameTime * 5.0; // Velocidad de movimiento en cuadrados/segundo
	game->rotSpeed = game->frameTime * 3.0;  // Velocidad de rotación en radianes/segundo
}

void	ft_drawStart_drawEnd(t_map *game)
{
	game->lineHeight = (int)(screenHeight / (game->perpWallDist + 0.5));
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
		game->sideDistY = (game->mapY + 1.0 - game->posY) * game->deltaDistY;
	}
}
int	get_pixel(t_image *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->size_l + x * (texture->bpp / 8));
	return (*(int *)pixel);
}

void	put_color_to_pixel(t_map *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_back(int width, int height, t_map *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y < height / 2)
				color = game->ceiling;
			else
				color = game->floor;
			put_color_to_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
}
void	draw_buffer(int width, int height, t_map *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	draw_back(width, height, game);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			color = game->buffer[y][x];
			if (color != 0)
				put_color_to_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0); //revisar img_data
}

void		ft_orientation(t_map *game)
{
	if (game->per == 'N')
	{
		game->dirX = -1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = 0.66;
	}
	else if (game->per == 'S')
	{
		game->dirX = 1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = -0.66;
	}
	else if (game->per == 'E')
	{
		game->dirX = 0;
		game->dirY = -1;
		game->planeX = -0.66;
		game->planeY = 0;
	}
	if (game->per == 'W')
	{
		game->dirX = 0;
		game->dirY = 1;
		game->planeX = 0.66;
		game->planeY = 0;
	}

}
void	*ft_load_images(t_map *game, int **texture, char *path)
{
	int width = texWidth;
    int height = texHeight;
	printf("%s\n", path);
	*texture = mlx_xpm_file_to_image(game->mlx_p, path, &width, &height);
	if (*texture == NULL)
	{
		write(2, "Error generating image\n", 24);
		exit (1);
	}
	return (*texture);
}
void	ft_upload_texture(t_map *game, int i)
{
	if (i == 0)
		game->texture[0]->t = ft_strdup(game->n_wall);
	if (i == 1)
		game->texture[1]->t = ft_strdup(game->s_wall);
	if (i == 2)
		game->texture[2]->t = ft_strdup(game->w_wall);
	if (i == 3)
		game->texture[3]->t = ft_strdup(game->e_wall);
}
void	ft_init_textures(t_map *game)
{
	int		i;
	int		w;
	int		h;

	i = 0;
	w = 64;
	h = 64;

	while (i < 4)
	{
		game->texture[i] = malloc(sizeof(t_image));
		if (!game->texture[i])
		{
			printf("Error\n");
			//fer free de tota la memoria i exit;
		}
		ft_upload_texture(game, i);
		printf("%s\n", game->texture[i]->t);
		game->texture[i]->imag = mlx_xpm_file_to_image(game->mlx_p, game->texture[i]->t, &w, &h);
		if (!game->texture[i]->imag)
		{
			printf("Error uploading textures\n");
			exit(1);
		}
		game->texture[i]->addr = mlx_get_data_addr(game->texture[i]->imag, &game->texture[i]->bpp, &game->texture[i]->size_l, &game->texture[i]->endian);
		i++;
		
	}
}
void	ray_dir_and_pos(t_map *game, int x)
{
	game->cameraX = 2 * x / (double)screenWidth - 1;
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)game->posX;
	game->mapY = (int)game->posY;
	game->sideDistX = 0;
	game->sideDistY = 0;
	if (game->rayDirX == 0)
		game->deltaDistX = 1e30;
	else
		game->deltaDistX = fabs(1 / game->rayDirX);
	if (game->rayDirY == 0)
		game->deltaDistY = 1e30;
	else
		game->deltaDistY = fabs(1 / game->rayDirY);
	game->perpWallDist = 0;
	game->stepX = 0;
	game->stepY = 0;
	game->hit = 0;
	game->side = 0;
}
void	ray_calc_sidedists(t_map *game)
{
	if (game->rayDirX < 0)
	{
		game->stepX = -1;
		game->sideDistX = (game->posX - game->mapX) * game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = (game->mapX + 1 - game->posX) * game->deltaDistX;
	}
	if (game->rayDirY < 0)
	{
		game->stepY = -1;
		game->sideDistY = (game->posY - game->mapY) * game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->mapY + 1 - game->posY) * game->deltaDistY;
	}
}
void	search_orientation(t_map *game)
{
	if (game->side == 0)
	{
		if (game->stepX > 0)
			game->hit_dir = S;
		else
			game->hit_dir = N;
	}
	else
	{
		if (game->stepY > 0)
			game->hit_dir = E;
		else
			game->hit_dir = W;
	}
}
void	ray_dda(t_map *game, char **map)
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
			game->mapY += game->stepY;
			game->side = 1;
		}
		if (map[game->mapX][game->mapY] == '1')
		{
			game->hit = 1;
			search_orientation(game);
		}
	}
	if (game->side == 0)
		game->perpWallDist = game->sideDistX - game->deltaDistX;
	else
		game->perpWallDist = game->sideDistY - game->deltaDistY;
}

void	calc_textures(t_texture *t, t_map *game, int line_heigth, int start)
{
	t->num = game->r_map[game->mapX][game->mapY] - 1;
	if (game->side == 0)
		t->wall_x = game->posY + game->perpWallDist * game->rayDirY;
	else
		t->wall_x = game->posX + game->perpWallDist * game->rayDirX;
	t->wall_x -= floor(t->wall_x);
	t->x = (int)(t->wall_x * (double)texWidth);
	if (game->side == 0 && game->rayDirX > 0)
		t->x = texWidth - t->x - 1;
	if (game->side == 1 && game->rayDirY < 0)
		t->x = texWidth - t->x - 1;
	t->step = 1.0 * texHeight / line_heigth;
	t->pos = (start - screenHeight / 2 + line_heigth / 2) * t->step;
}

void	fill_buffer(int start, int end, t_map *game, int x)
{
	int	color;
	int	j;

	j = start;
	game->tex.num = game->hit_dir;
	while (j < end)
	{
		game->tex.y = (int)game->tex.pos & (texHeight - 1);
		game->tex.pos += game->tex.step;
		game->tex.x = (int)(game->tex.wall_x * (double)texWidth);
		color = get_pixel(game->texture[game->tex.num], game->tex.x, game->tex.y);
		if (color < 0)
			color = color * -1;
		if (game->side == 1)
			color = (color >> 1) & 8355711;
		game->buffer[j][x] = color;
		j++;
	}
}
void	prepare_draw_cub(t_map *game, int x)
{
	int	line_heigth;
	int	draw_start;
	int	draw_end;

	line_heigth = (int)(screenHeight / game->perpWallDist);
	draw_start = -line_heigth / 2 + screenHeight / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_heigth / 2 + screenHeight / 2;
	if (draw_end >= screenHeight)
		draw_end = screenHeight - 1;
	calc_textures(&game->tex, game, line_heigth, draw_start);
	fill_buffer(draw_start, draw_end, game, x);
}
void	clean_buffer(t_map *game, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			game->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}
int	draw_cub(t_map *game)
{
	int	x;
	int	w;
	int	h;

	w = screenWidth;
	h = screenHeight;
	x = 0;
	createImage(game);
	while (x < screenWidth)
	{
		ray_dir_and_pos(game, x);
		ray_calc_sidedists(game);
		ray_dda(game, game->r_map);
		prepare_draw_cub(game, x);
		x++;
	}
	draw_buffer(screenWidth, screenHeight, game);
	clean_buffer(game, screenWidth, screenHeight);
	mlx_clear_window(game->mlx_p, game->win_p);
	mlx_put_image_to_window(game->mlx_p, game->win_p, game->img_p, 0, 0);
	/*cub->ray.move_speed = MOVE_SPEED;
	cub->ray.rot_speed = ROT_SPEED;*/
	return (0); //revisar
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
	game.oldTime = getTicks(); // revisar
	game.posX = game.x;
	game.posY = game.y;
	ft_orientation(&game);
	game.r_map = (char	**)malloc(game.height * sizeof(char *));
	if (game.r_map == NULL)
		printf("Null game.r_map\n");
	i = 0;
	while(i < game.height)
	{
		game.r_map[i] = (char *)malloc(game.width * sizeof(char) + 1);
		if (game.r_map[i] == NULL)
			printf("game.r_map[i] == NULL\n");
		i++;
	}
	i = game.map_coor;
	j = 0;
	int p = 0;

	while (i < game.height + game.map_coor)
	{
		while(game.map[i][j] != 10)
		{
			game.r_map[p][j] = game.map[i][j];
			j++;
		}
		i++;
		p++;
		j = 0;
	}
	i = 0;
	j = 0;
	game.mlx_p = mlx_init();
	game.win_p = mlx_new_window(game.mlx_p, screenWidth, screenHeight, "cub3d");
	ft_init_textures(&game);
	mlx_work_exec(&game);
	return (0);
}
