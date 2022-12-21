/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:31:44 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/21 16:28:30 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

void	death(t_data *data)
{
	static int	i;

	if (i >= 50)
		handle_destroy(data);
	if (i / 4 < 8)
	{
		render_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->t.p_die[i / 4],
			data->player.img_x, data->player.img_y);
	}
	i++;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 49)
		data->view = -1;
	if (keysym == 53)
		handle_destroy(data);
	if (data->moving != 0)
		return (0);
	if (valid_move(keysym, data, 'e') && obj_count(data, 'c') == 0)
		exit(0);
	if (valid_move(keysym, data, '1') != 0
		|| valid_move(keysym, data, 'e') != 0)
		return (0);
	if (keysym == 13 || keysym == 126)
		data->view = 1;
	if (keysym == 0 || keysym == 123)
		data->view = 2;
	if (keysym == 1 || keysym == 125)
		data->view = 3;
	if (keysym == 2 || keysym == 124)
		data->view = 4;
	data->moving = data->view;
	if (data->view != 0 && data->view != -1)
		data->moves++;
	return (0);
}

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}
