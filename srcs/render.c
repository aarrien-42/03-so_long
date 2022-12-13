/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:47:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 18:43:33 by aarrien-         ###   ########.fr       */
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
