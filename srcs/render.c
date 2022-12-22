/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:47:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/22 14:29:35 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	put_image(t_data *data, void **img, int pos[2], int mode)
{
	static int	i;

	mlx_put_image_to_window(data->mlx, data->win, img[0], pos[0], pos[1]);
	if (mode == 1 || mode == 2)
		mlx_put_image_to_window(data->mlx, data->win, img[1],
			pos[0], (pos[1] - 32));
	if (mode == 2 && obj_count(data, 'c') == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, img[2], pos[0], pos[1]);
		i++;
		if (i >= 64)
			i = 0;
		mlx_put_image_to_window(data->mlx, data->win,
			data->t.par[i / 8], pos[0], pos[1]);
	}
	return (0);
}

int	render_objects(t_data *data, int x, int y)
{
	int	pos[2];

	pos[0] = x * 32;
	pos[1] = y * 32;
	if (data->map[y][x] == '1')
		put_image(data, data->t.wall, pos, 0);
	if (data->map[y][x] == 'c')
		put_image(data, data->t.chest, pos, 0);
	if (data->map[y][x] == 'e')
		put_image(data, data->t.exit, pos, 2);
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
			mlx_put_image_to_window(data->mlx, data->win,
				data->t.floor[0], i * 32, j * 32);
			render_objects(data, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	scan_enemies(data);
	show_info(data);
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
			str[i] = 'C';
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
	if (count % 350 == 0)
	{
		count = 0;
		if (++i >= 16)
			i = 0;
		check_view(data);
		if (data->view == 0)
		{
			render_map(data);
			mlx_put_image_to_window(data->mlx, data->win, data->t.p_wait[i / 4],
				data->player.img_x, data->player.img_y);
		}
		if (data->view == -1)
			death(data);
		if (data->map[data->player.img_y / 32][data->player.img_x / 32] == 'c')
			collect_chest(data, data->player.img_x / 32,
				data->player.img_y / 32);
		check_die(data);
	}
	return (0);
}
