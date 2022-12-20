/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:31:44 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/20 18:16:00 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	valid_move(int keysym, t_data *data, char obj)
{
	int	p_x;
	int	p_y;

	p_x = data->player.img_x / 32;
	p_y = data->player.img_y / 32;
	if (keysym == 13 || keysym == 126)
		if (data->map[p_y - 1][p_x] == obj)
			return (1);
	if (keysym == 0 || keysym == 123)
		if (data->map[p_y][p_x - 1] == obj)
			return (1);
	if (keysym == 1 || keysym == 125)
		if (data->map[p_y + 1][p_x] == obj)
			return (1);
	if (keysym == 2 || keysym == 124)
		if (data->map[p_y][p_x + 1] == obj)
			return (1);
	return (0);
}

void	death(t_data *data)
{
	
}

int	handle_keypress(int keysym, t_data *data)
{
	printf("Keypress: %d\n", keysym);
	if (keysym == 49)
		death(data);
	if (keysym == 53)
		handle_destroy(data);
	if (data->moving != 0)
		return (0);
	if (valid_move(keysym, data, 'E') && obj_count(data, 'C') == 0)
		exit(0);
	if (valid_move(keysym, data, '1') != 0
		|| valid_move(keysym, data, 'E') != 0)
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
	if (data->view != 0)
		data->moves++;
	return (0);
}

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}
