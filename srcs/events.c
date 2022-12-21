/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:31:44 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/21 15:19:59 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

void	show_error(int code)
{
	ft_putstr_fd("Error\n", 2);
	if (code == 0)
		ft_putstr_fd("Invalid input\n", 2);
	if (code == 1)
		ft_putstr_fd("Invalid file extension\n", 2);
	if (code == 2)
		ft_putstr_fd("Unable to read from the file\n", 2);
	if (code == 3)
		ft_putstr_fd("Not a single collectable\n", 2);
	if (code == 4)
		ft_putstr_fd("Invalid number of players\n", 2);
	if (code == 5)
		ft_putstr_fd("Invalid number of exits\n", 2);
	if (code == 6)
		ft_putstr_fd("The map is not a rectangle\n", 2);
	if (code == 7)
		ft_putstr_fd("The map is not fully closed\n", 2);
	if (code == 8)
		ft_putstr_fd("Imposible map\n", 2);
	exit(0);
}

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
