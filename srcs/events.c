/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:31:44 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 13:41:36 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	move(int keysym, t_data *data)
{
	if (keysym == 13) // w
	{
		data->view = 0;
		data->player.img_y -= 32;
	}
	if (keysym == 0) // a
	{
		data->view = 1;
		data->player.img_x -= 32;
	}
	if (keysym == 1) // s
	{
		data->view = 2;
		data->player.img_y += 32;
	}
	if (keysym == 2) // d
	{
		data->view = 3;
		data->player.img_x += 32;
	}
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	printf("Keypress: %d\n", keysym);
	if (keysym == 53) // esc
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	move(keysym, data);
	load_background(data, 480, 480);
	return (0);
}

int	handle_destroy(t_data *data)
{
	printf("Destroy\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}
