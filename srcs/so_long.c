/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:26:05 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 13:47:41 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"



int	player_init(t_data *data)
{
	data->view = 3;
	data->player.img_x = 32;
	data->player.img_y = 0;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.player_right[0], data->player.img_x, data->player.img_y);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480 , "so_long");
	load_textures(&data);
	load_background(&data, 480, 480);
	player_init(&data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_hook(data.win_ptr, 2, (1L<<0), &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, &handle_destroy, &data); // close window
	mlx_loop(data.mlx_ptr);
	return (0);
}

