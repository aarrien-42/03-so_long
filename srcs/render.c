/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:47:22 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 14:08:22 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	load_n(t_data *data, void **w, char *path, int n)
{
	int		i;
	char	*s;
	char	*s1;
	char	*s2;

	i = 0;
	while (i < n)
	{
		s2 = malloc(2 * sizeof(char));
		s2[0] = i + '0';
		s2[1] = '\0';
		s1 = ft_strjoin(path, s2);
		s = ft_strjoin(s1, ".xpm");
		w[i] = mlx_xpm_file_to_image(data->mlx_ptr, s, &data->player.img_width, &data->player.img_height);
		free(s);
		free(s1);
		free(s2);
		i++;
	}
	return (0);
}

int	load_textures(t_data *data)
{
	load_n(data, data->t.player_up, "./textures/player/up/player_up_", 8);
	load_n(data, data->t.player_down, "./textures/player/down/player_down_", 8);
	load_n(data, data->t.player_right, "./textures/player/right/player_right_", 8);
	load_n(data, data->t.player_left, "./textures/player/left/player_left_", 8);
	return (0);
}

int	load_background(t_data *data, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->t.floor = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor/floor.xpm", &data->floor.img_width, &data->floor.img_height);
	while (i < height)
	{
		while (j < width)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.floor, i, j);
			j += 32;
		}
		j = 0;
		i += 32;
	}
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->view == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.player_up[0], data->player.img_x, data->player.img_y);
	if (data->view == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.player_left[0], data->player.img_x, data->player.img_y);
	if (data->view == 2)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.player_down[0], data->player.img_x, data->player.img_y);
	if (data->view == 3)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->t.player_right[0], data->player.img_x, data->player.img_y);
	return (0);
}
