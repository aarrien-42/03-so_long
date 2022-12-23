/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/23 13:21:44 by aarrien-         ###   ########.fr       */
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
	void	*p_die[8];
	void	*p_up[8];
	void	*p_down[8];
	void	*p_right[8];
	void	*p_left[8];
	void	*floor[10];
	void	*wall[1];
	void	*chest[1];
	void	*exit[3];
	void	*par[8];
	void	*spike[3];
}			t_texture;

typedef struct s_img {
	int		img_w;
	int		img_h;
	int		img_x;
	int		img_y;
}			t_img;

typedef struct s_enemy {
	int	mode;
	int	dir;
}			t_enemy;

typedef struct s_data {
	void		*mlx;
	void		*win;
	char		**map;
	int			map_w;
	int			map_h;
	t_texture	t;
	t_enemy		e;
	t_img		player;
	int			view;
	int			moving;
	size_t		moves;
	int			chests_init;
}				t_data;

/*-SO_LONG-*/
int		game_init(t_data *data);

/*-MAP-*/
int		get_height(char *map);
int		get_width(t_data *data);
int		save_map(t_data *data, char *map, int h);
int		print_map(t_data *data);

/*-CHECK-*/
int		check_rect(t_data *data);
int		check_border(t_data *data);
int		paint_floor(t_data *data, int x, int y);
int		check_valid_letters(t_data *data);
int		check_map(t_data *data, char *input);

/*-UTILS-*/
int		show_info(t_data *data);
void	show_error(int code);
int		*find(t_data *data, char c);
int		obj_count(t_data *data, char c);
int		valid_move(int keysym, t_data *data, char obj);

/*-EVENTS-*/
void	death(t_data *data);
int		check_die(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_destroy(t_data *data);

/*-LOAD-*/
int		load_n(t_data *data, void **w, char *path, int n);
int		load_textures(t_data *data);

/*-ENEMY-*/
int		put_enemy(t_data *data, int x, int y, int mode);
int		check_enemy(t_data *data, int x, int y);
int		scan_enemies(t_data *data);
int		move_enemy(t_data *data);

/*-ANIMATE-*/
int		check_view(t_data *data);
int		move_player(t_data *data, void **move, int i);
int		animate_move(t_data *data, void **move, int frames);

/*-RENDER-*/
int		put_image(t_data *data, void **img, int pos[2], int mode);
int		render_objects(t_data *data, int x, int y);
int		render_map(t_data *data);
int		collect_chest(t_data *data, int x, int y);
int		render_next_frame(t_data *data);

#endif
