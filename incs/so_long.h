/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/12 17:28:18 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"
# include "../mlx/mlx.h"

typedef struct s_img {
	void	*img_ptr[4];
	int		img_width;
	int		img_height;
	int		img_x;
	int		img_y;
	int		view;
}			t_img;

typedef struct s_space {
	void	*img_ptr;
	int		img_width;
	int		img_height;
	int		img_x;
	int		img_y;
	int		position;
}				t_space;

typedef struct s_data {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		player;
	t_space		floor;
	t_space		wall;
}				t_data;

/*-SO_LONG-*/

#endif
