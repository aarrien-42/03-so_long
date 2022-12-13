/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:26:05 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 18:32:41 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	player_init(t_data *data)
{
	data->moves = 0;
	data->moving = 0;
	data->view = 0;
	data->player.img_x = 0;
	data->player.img_y = 0;
	mlx_put_image_to_window(data->mlx, data->win, data->t.p_wait[0],
		data->player.img_x, data->player.img_y);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.map_w = 480 * 2;
	data.map_h = 480 * 2;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map_w, data.map_h, "so_long");
	load_textures(&data);
	render_map(&data);
	player_init(&data);
	mlx_hook(data.win, 2, (1L << 0), &handle_keypress, &data);
	mlx_hook(data.win, 17, 0, &handle_destroy, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
