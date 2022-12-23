/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:36:01 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/23 13:37:10 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	put_enemy(t_data *data, int x, int y, int mode)
{
	if (y < 0 || x < 0 || y > data->map_h / 32 - 1)
		return (0);
	if (data->map[y][x] == 'X' ||
		data->map[y][x] == 'v' || data->map[y][x] == 'V' ||
		data->map[y][x] == 'h' || data->map[y][x] == 'H')
		mlx_put_image_to_window(data->mlx, data->win,
			data->t.spike[mode], x * 32, y * 32);
	return (0);
}

int	check_enemy(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'v' || data->map[y][x] == 'V')
	{
		put_enemy(data, x, y - 1, 0);
		put_enemy(data, x, y, 0);
		put_enemy(data, x, y + 1, 0);
		if (data->e.mode == -1)
			put_enemy(data, x, y - 1, 2);
		if (data->e.mode == 0)
			put_enemy(data, x, y, 2);
		if (data->e.mode == 1)
			put_enemy(data, x, y + 1, 2);
	}
	if (data->map[y][x] == 'h' || data->map[y][x] == 'H')
	{
		put_enemy(data, x - 1, y, 0);
		put_enemy(data, x, y, 0);
		put_enemy(data, x + 1, y, 0);
		if (data->e.mode == -1)
			put_enemy(data, x - 1, y, 2);
		if (data->e.mode == 0)
			put_enemy(data, x, y, 2);
		if (data->e.mode == 1)
			put_enemy(data, x + 1, y, 2);
	}
	return (0);
}

int	scan_enemies(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < (data->map_h / 32))
	{
		while (i < (data->map_w / 32))
		{
			check_enemy(data, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	move_enemy(t_data *data)
{
	if (data->e.dir == 1)
	{
		data->e.mode++;
		if (data->e.mode == 1)
			data->e.dir = -1;
	}
	else
	{
		data->e.mode--;
		if (data->e.mode == -1)
			data->e.dir = 1;
	}
	return (0);
}
