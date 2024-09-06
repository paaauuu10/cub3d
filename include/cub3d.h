/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:58:47 by pborrull          #+#    #+#             */
/*   Updated: 2024/09/05 13:06:56 by pbotargu         ###   ########.fr       */
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
	int		per;
	char	**map_pos;
	void	*mlx_p;
	void	*win_p;
	char	**map;
	void	*player;
	void	*floor;
	void	*ceiling;
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
}	t_map;

# define TILE_SIZE 15
# define MINIMAP_SIZE 15
# define MINIMAP_PIXEL_SIZE 225
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

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
void	ft_draw_player(t_map *game);
void	ft_draw_big_map(t_map *game);

#endif
