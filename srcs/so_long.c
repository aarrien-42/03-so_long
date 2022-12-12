/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:26:05 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/12 17:38:42 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keysym, t_data *data)
{
	printf("Keypress: %d\n", keysym);
	if (keysym == 53) // esc
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	if (keysym == 13) // w
	{
		data->player.view = 0;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr, data->player.img_x, data->player.img_y);
		data->player.img_y -= 32;
	}
	if (keysym == 0) // a
	{
		data->player.view = 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr, data->player.img_x, data->player.img_y);
		data->player.img_x -= 32;
	}
	if (keysym == 1) // s
	{
		data->player.view = 2;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr, data->player.img_x, data->player.img_y);
		data->player.img_y += 32;
	}
	if (keysym == 2) // d
	{
		data->player.view = 3;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr, data->player.img_x, data->player.img_y);
		data->player.img_x += 32;
	}
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	printf("Keyrelease: %d\n", keysym);
	(void)data;
	return (0);
}

int	handle_destroy(t_data *data)
{
	printf("Destroy\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	load_player(t_data *data, int x, int y)
{
	data->player.img_x = x;
	data->player.img_y = y;
	data->player.img_ptr[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player/player_w.xpm", &data->player.img_width, &data->player.img_height);
	data->player.img_ptr[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player/player_a.xpm", &data->player.img_width, &data->player.img_height);
	data->player.img_ptr[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player/player_s.xpm", &data->player.img_width, &data->player.img_height);
	data->player.img_ptr[3] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player/player_d.xpm", &data->player.img_width, &data->player.img_height);
	return (0);
}

int	load_background(t_data *data, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->floor.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor/floor.xpm", &data->floor.img_width, &data->floor.img_height);
	while (i < height)
	{
		while (j < width)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr, i, j);
			j += 32;
		}
		j = 0;
		i += 32;
	}
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->player.view == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr[0], data->player.img_x, data->player.img_y);
	if (data->player.view == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr[1], data->player.img_x, data->player.img_y);
	if (data->player.view == 2)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr[2], data->player.img_x, data->player.img_y);
	if (data->player.view == 3)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr[3], data->player.img_x, data->player.img_y);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480 , "so_long");
	load_player(&data, 100, 100);
	load_background(&data, 480, 480);
	data.player.view = 3;
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_hook(data.win_ptr, 2, (1L<<0), &handle_keypress, &data);
	mlx_hook(data.win_ptr, 3, (1L<<1), &handle_keyrelease, &data);
	mlx_hook(data.win_ptr, 17, 0, &handle_destroy, &data); // close window
	mlx_loop(data.mlx_ptr);
	return (0);
}

