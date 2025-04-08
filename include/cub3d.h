/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:58:47 by pborrull          #+#    #+#             */
/*   Updated: 2024/10/01 12:03:29 by pborrull         ###   ########.fr       */
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
# include <stdint.h>
# include <sys/time.h>

# define SCREENWIDTH 	1280
# define SCREENHEIGHT 	960
# define TEXWIDTH 		64
# define TEXHEIGHT 		64
# define N 0
# define S 1
# define W 2
# define E 3
# define TILE_SIZE 32
# define MINIMAP_SIZE 6
# define MINIMAP_PIXEL_SIZE 192
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

typedef struct s_texture
{
	int			num; //type of texture
	double		wall_x; //exact position where the wall is hitted
	int			x; //x coor texture
	int			y; //y coor texture
	double		step;
	double		pos;
}	t_texture;

typedef struct s_image
{
	void		*imag;
	char		*addr;
	char		*t;
	int			size_l;
	int			bpp;
	int			endian;
}	t_image;

typedef struct s_map
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			param;
	int			fd;
	int			i;
	char		per;
	char		**map_pos;
	void		*mlx_p;
	void		*win_p;
	char		**map;
	void		*player;
	int			floor;
	int			ceil;
	char		*n_wall;
	char		*s_wall;
	char		*e_wall;
	char		*w_wall;
	int			start_x;
	int			start_y;
	int			current_x;
	int			current_y;
	int			x_pos;
	int			x_posl;
	int			y_pos;
	int			y_posl;
	void		*img_p;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			hit_dir;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		perpwalldist;
	char		**r_map;
	int			map_coor;
	uint32_t	buffer[SCREENHEIGHT][SCREENWIDTH];
	t_image		*texture[4];
	t_texture	tex;
	void		*im;
}	t_map;

void	ft_parser(t_map *game);
int		ft_isspace(char s);
int		ft_line_bef(char **map, int i, int j);
char	*ft_no_spaces(t_map *game, int k, char *param);
int		deal_key(int key, t_map *game);
int		ft_map_reading(t_map *game, char **s);
int		mouse_hook(t_map *game);
int		ft_exit(t_map *game, char *s);
int		calculate_start_x(t_map *game);
int		calculate_start_y(t_map *game);
void	draw_map(t_map *game);
void	ft_draw_player(t_map *game, int flag);
int		ft_obtcolor(t_map *game, char *s);
int		calc_width(t_map *game, char *s);
int		handle_key(int keycode, t_map *game);
void	game_loop(t_map	*game);
int		ft_draw_cub(t_map *game);
void	ft_draw_lines(t_map *game);

/*---------------------- TEXTURES -----------------------*/
void	ft_first_image(t_map *game);
void	ft_init_textures(t_map *game);

/*--------------------- RAYCASTING ----------------------*/
int		ft_draw_cub(t_map *game);

/*--------------------- BUFFER --------------------------*/
void	ft_draw_back(int width, int height, t_map *game);
void	ft_draw_buffer(int width, int height, t_map *game);
void	ft_buffer_clean(t_map *game, int w, int h);

/*--------------------- PIXELS --------------------------*/
int		ft_get_pixel(t_image *texture, int x, int y);
void	ft_put_color_to_pixel(t_map *game, int x, int y, int color);

/*--------------------- UTILS ---------------------------*/
void	ft_orientation(t_map *game);
void	ft_calc_text(t_texture *t, t_map *game, int line_heigth, int start);
void	ft_buffer_fill(int start, int end, t_map *game, int x);
void	ft_start_end(t_map *game, int x);
void	ft_search_orientation(t_map *game);
char	*ft_textures(char *s);

#endif
