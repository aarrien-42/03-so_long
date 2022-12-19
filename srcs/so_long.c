/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:26:05 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/19 19:00:23 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	*find(t_data *data, char c)
{
	int	*res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = malloc(2 * sizeof(int));
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (data->map[j][i] == c)
			{
				res[0] = i * 32;
				res[1] = j * 32;
				return (res);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	game_init(t_data *data)
{
	load_textures(data);
	render_map(data);
	data->moves = 0;
	data->moving = 0;
	data->view = 0;
	data->chests_init = obj_count(data, 'C');
	data->player.img_x = find(data, 'P')[0];
	data->player.img_y = find(data, 'P')[1];
	mlx_put_image_to_window(data->mlx, data->win, data->t.p_wait[0],
		data->player.img_x, data->player.img_y);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if (check_map(&data, av[1]) != 0)
		return (ft_putstr_fd("Error\n", 2), 0);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map_w, data.map_h, "so_long");
	game_init(&data);
	mlx_hook(data.win, 2, (1L << 0), &handle_keypress, &data);
	mlx_hook(data.win, 17, 0, &handle_destroy, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
