/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:47:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/16 15:05:19 by aarrien-         ###   ########.fr       */
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

int	put_image(t_data *data, void **img, int x, int y, int mode)
{
	mlx_put_image_to_window(data->mlx, data->win, img[0], x * 32, y * 32);
	if (mode == 1) // first state of a 32 x 64 object
		mlx_put_image_to_window(data->mlx, data->win, img[1], x * 32, (y - 1) * 32);
	if (mode == 2) // second state of a 32 x 64 object
		put_image(data, &img[2], x, y, 1);
	if (mode == 3) // exit's lights
	{
		/*if (chest_count(data) * 10 / data->chests_init <= data->chests_init / 4) // first light
			mlx_put_image_to_window(data->mlx, data->win, img[2], x * 32, y * 32);
		if (chest_count(data) * 10 / data->chests_init <= data->chests_init / 3) // second light
			mlx_put_image_to_window(data->mlx, data->win, img[3], x * 32, y * 32);
		if (chest_count(data) * 10 / data->chests_init <= data->chests_init / 2) // third light
			mlx_put_image_to_window(data->mlx, data->win, img[4], x * 32, y * 32);
		if (chest_count(data) == 0) // all
		{
			mlx_put_image_to_window(data->mlx, data->win, img[5], x * 32, y * 32);
			mlx_put_image_to_window(data->mlx, data->win, img[6], x * 32, (y - 1) * 32);
		}*/
	}
	return (0);
}

int	render_objects(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		put_image(data, data->t.wall, x, y, 0);
	if (data->map[y][x] == 'C')
		put_image(data, data->t.chest, x, y, 1);
	if (data->map[y][x] == 'c')
		put_image(data, data->t.chest, x, y, 2);
	if (data->map[y][x] == 'E')
	{
		put_image(data, data->t.exit, x, y, 1);
	}
	return (0);
}

int	render_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx_clear_window(data->mlx, data->win);
	while (j < (data->map_h / 32))
	{
		while (i < (data->map_w / 32))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->t.floor[0], i * 32, j * 32);
			render_objects(data, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	show_moves(data);
	return (0);
}

int	collect_chest(t_data *data, int x, int y)
{
	char	*str;
	char	*aux;
	int		i;

	i = 0;
	aux = data->map[y];
	str = malloc ((ft_strlen(aux) + 1) * sizeof(char));
	while (aux[i])
	{
		if (i == x)
			str[i] = 'c';
		else
			str[i] = aux[i];
		i++;
	}
	str[i] = '\0';
	data->map[y] = str;
	free(aux);
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
		if (data->map[data->player.img_y / 32][data->player.img_x / 32] == 'C')
			collect_chest(data, data->player.img_x / 32, data->player.img_y / 32);
	}
	printf("CHESTS = %d\n", chest_count(data));
	//printf("Position: x %d y %d\n", data->player.img_x, data->player.img_y);
	//printf("Moves = %zu\n", data->moves);
	return (0);
}
