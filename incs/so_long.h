/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/19 13:17:04 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "../incs/libft.h"
# include "../mlx/mlx.h"

typedef struct s_texture {
	void	*p_wait[4];
	void	*p_up[8];
	void	*p_down[8];
	void	*p_right[8];
	void	*p_left[8];
	void	*floor[10];
	void	*wall[1];
	void	*chest[4];
	void	*exit[7];
}			t_texture;

typedef struct s_img {
	int		img_w;
	int		img_h;
	int		img_x;
	int		img_y;
}			t_img;

typedef struct s_data {
	void		*mlx;
	void		*win;
	char		**map;
	int			map_w;
	int			map_h;
	t_texture	t;
	t_img		player;
	int			view;
	int			moving;
	size_t		moves;
	int			chests_init;
}				t_data;

/*-SO_LONG-*/

/*-CHECK-*/
int	get_height(char *map);
int	get_width(t_data *data);
int	save_map(t_data *data, char *map, int h);
int	print_map(t_data *data);
int	chest_count(t_data *data);
int	check_map(t_data *data, char *input);

/*-EVENTS-*/
int	valid_move(int keysym, t_data *data, char obj);
int	controls(int keysym, t_data *data);
int	handle_keypress(int keysym, t_data *data);
int	handle_destroy(t_data *data);

/*-LOAD-*/
int	load_n(t_data *data, void **w, char *path, int n);
int	load_textures(t_data *data);

/*-RENDER-*/
int	move_player(t_data *data, void **move, int i);
int	animate_move(t_data *data, void **move, int frames);
int	render_map(t_data *data);
int	put_image(t_data *data, void **img, int pos[2], int mode);
int	render_next_frame(t_data *data);

#endif
