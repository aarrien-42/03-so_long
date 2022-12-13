/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:30:48 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 18:05:26 by aarrien-         ###   ########.fr       */
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
		w[i] = mlx_xpm_file_to_image(data->mlx, s,
				&data->player.img_w, &data->player.img_h);
		free(s);
		free(s1);
		free(s2);
		i++;
	}
	return (0);
}

int	load_textures(t_data *data)
{
	load_n(data, data->t.p_wait, "./textures/player/wait/player_wait_", 4);
	load_n(data, data->t.p_up, "./textures/player/up/player_up_", 8);
	load_n(data, data->t.p_down, "./textures/player/down/player_down_", 8);
	load_n(data, data->t.p_right, "./textures/player/right/player_right_", 8);
	load_n(data, data->t.p_left, "./textures/player/left/player_left_", 8);
	load_n(data, data->t.floor, "./textures/floor/floor_", 2);
	return (0);
}

int	render_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx_clear_window(data->mlx, data->win);
	while (i < data->map_w)
	{
		while (j < data->map_h)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->t.floor[0], i, j);
			if (i == 0)
				mlx_put_image_to_window(data->mlx, data->win, data->t.floor[1], i, j);
			j += 32;
		}
		j = 0;
		i += 32;
	}
	return (0);
}