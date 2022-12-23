/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:26:05 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/23 13:16:43 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	game_init(t_data *data)
{
	load_textures(data);
	data->moves = 0;
	data->moving = 0;
	data->view = 0;
	data->chests_init = obj_count(data, 'c');
	data->player.img_x = find(data, 'P')[0];
	data->player.img_y = find(data, 'P')[1];
	data->e.mode = 0;
	data->e.dir = 1;
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->t.p_wait[0],
		data->player.img_x, data->player.img_y);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		show_error(0);
	check_map(&data, av[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map_w, data.map_h, "so_long");
	game_init(&data);
	mlx_hook(data.win, 2, (1L << 0), &handle_keypress, &data);
	mlx_hook(data.win, 17, 0, &handle_destroy, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
