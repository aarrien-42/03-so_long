/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:47:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/14 11:52:08 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	move_player(t_data *data, void **move, int i)
{
	render_map(data);
	if (data->view == 1)
		data->player.img_y -= 4;
	if (data->view == 2)
		data->player.img_x -= 4;
	if (data->view == 3)
		data->player.img_y += 4;
	if (data->view == 4)
		data->player.img_x += 4;
	mlx_put_image_to_window(data->mlx, data->win, move[i],
		data->player.img_x, data->player.img_y);
	return (0);
}

int	animate_move(t_data *data, void **move, int frames)
{
	static int	count;
	static int	i;

	count++;
	if (count % 8 == 0)
	{
		move_player(data, move, i);
		count = 0;
		if (++i >= frames)
		{
			i = 0;
			data->moving = 0;
			data->view = 0;
		}
	}
	return (0);
}

int	show_moves(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 5, 15, 0x00FFFFFF, "MOVES:");
	mlx_string_put(data->mlx, data->win, 50, 15, 0x00FFFFFF, ft_itoa(data->moves));
	return (0);
}

int	render_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx_clear_window(data->mlx, data->win);
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			mlx_put_image_to_window(data->mlx, data->win, data->t.floor[0], i * 32, j * 32);
			if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->t.floor[1], i * 32, j * 32);
			i++;
		}
		i = 0;
		j++;
	}
	show_moves(data);
	return (0);
}

int	render_next_frame(t_data *data)
{
	static int	count;
	static int	i;

	count++;
	if (count % 64 == 0)
	{
		count = 0;
		if (++i >= 32)
			i = 0;
		if (data->view == 1 && data->moving == 1)
			animate_move(data, data->t.p_up, 8);
		if (data->view == 2 && data->moving == 2)
			animate_move(data, data->t.p_left, 8);
		if (data->view == 3 && data->moving == 3)
			animate_move(data, data->t.p_down, 8);
		if (data->view == 4 && data->moving == 4)
			animate_move(data, data->t.p_right, 8);
		if (data->view == 0)
		{
			render_map(data);
			mlx_put_image_to_window(data->mlx, data->win, data->t.p_wait[i / 8],
				data->player.img_x, data->player.img_y);
		}
	}
	//printf("Position: x %d y %d\n", data->player.img_x, data->player.img_y);
	//printf("Moves = %zu\n", data->moves);
	return (0);
}
