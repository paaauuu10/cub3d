/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:58:47 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/22 13:11:47 by pborrull         ###   ########.fr       */
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

#endif

