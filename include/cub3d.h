/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:58:47 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/26 12:57:42 by pborrull         ###   ########.fr       */
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
	int		param;
	int		fd;
	int		i;
	int		per;
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
}	t_map;

int	parser(t_map *game);
int	deal_key(int key, t_map *game);
int	map_reading(t_map *game, char **s);
int	mouse_hook(t_map *game);
int	ft_exit(t_map *game, char *s);

#endif

