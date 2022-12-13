/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 14:08:08 by aarrien-         ###   ########.fr       */
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

typedef struct s_texture {
	void	*player_up[8];
	void	*player_down[8];
	void	*player_right[8];
	void	*player_left[8];
	void	*floor;
}			t_texture;

typedef struct s_img {
	int		img_width;
	int		img_height;
	int		img_x;
	int		img_y;
}			t_img;

typedef struct s_data {
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	t;
	t_img		player;
	int			view;
	t_img		floor;
	t_img		wall;
}				t_data;

/*-SO_LONG-*/
int	load_textures(t_data *data);
int	load_background(t_data *data, int width, int height);
int	render_next_frame(t_data *data);

/*-EVENTS-*/
int	handle_keypress(int keysym, t_data *data);
int	handle_destroy(t_data *data);

/*-RENDER-*/
int	load_n(t_data *data, void **w, char *path, int n);
int	load_textures(t_data *data);
int	load_background(t_data *data, int width, int height);
int	render_next_frame(t_data *data);

#endif
