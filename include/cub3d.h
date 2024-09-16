/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:58:47 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/13 11:57:30 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h> // Para uint8_t

typedef struct s_ColorRGB 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}	t_ColorRGB;

# define RGB_Red   (t_ColorRGB){255, 0, 0}
# define RGB_Green (t_ColorRGB){0, 255, 0}
# define RGB_Blue  (t_ColorRGB){0, 0, 255}
# define RGB_White (t_ColorRGB){255, 255, 255}
# define RGB_Yellow (t_ColorRGB){255, 255, 0}

# define mapWidth 2048
# define mapHeight 1024
# define screenWidth 2048
# define screenHeight 1024

# define TILE_SIZE 32
# define MINIMAP_SIZE 6
# define MINIMAP_PIXEL_SIZE 192
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

#define UP_KEY 119       // Tecla W
#define DOWN_KEY 115     // Tecla S
#define LEFT_KEY 97      // Tecla A
#define RIGHT_KEY 100    // Tecla D
#define ESC_KEY 65307    // Tecla Escape

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		height;

	int		w_map;
	int		h_map;
	int		param;
	int		fd;
	int		i;
	char	per;
	char	**map_pos;
	void	*mlx_p;
	void	*win_p;
	char	**map;
	void	*player;
	int		floor;
	int		ceiling;
	void	*n_wall;
	void	*s_wall;
	void	*e_wall;
	void	*w_wall;
	int		start_x;
	int		start_y;
	int		current_x;
	int		current_y;
	int		dir_x;
	int		dir_y;
	int		x_pos;
	int		x_posl;
	int		y_pos;
	int		y_posl;
    void *img_p;
    char *img_data;
    int bpp;
    int size_line;
    int endian;

	//afegides per dividir funcions
	double	oldTime;
	double	time;
	double frameTime;
	
	//x and y player's start positon
	double	posX;
	double	posY; 
	
	//initial direction vector
	double	dirX; 
	double	dirY;
	
	//the 2d raycaster version of camera plane
	double	planeX;
	double	planeY;

	//x-coordinate in camera space
	double		cameraX;

	double		rayDirX;
	double		rayDirY;

	int			mapX;
	int			mapY;

	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;

	int			stepX;
	int			stepY;

	int			hit;
	int			side;

	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	// Velocidad de movimiento en cuadrados/segundo
	double		moveSpeed;
	
	// Velocidad de rotación en radianes/segundo
	double		rotSpeed;


	double		perpWallDist;
	t_ColorRGB	color;

	int			**map_real;
}	t_map;

void	parser(t_map *game);
int		ft_isspace(char s);
int		ft_line_bef(char **map, int i, int j);
char	*ft_no_spaces(t_map *game, int k, char *param);
int		deal_key(int key, t_map *game);
int		map_reading(t_map *game, char **s);
int		mouse_hook(t_map *game);
int		ft_exit(t_map *game, char *s);
int		calculate_start_x(t_map *game);
int		calculate_start_y(t_map *game);
void	draw_map(t_map *game);
void	ft_draw_player(t_map *game, int flag);
void	ft_draw_big_map(t_map *game);
int		ft_obtain_color(char *s);
int		calc_width(t_map *game, char *s);
int 	handle_key(int keycode, t_map *game);

#endif
