/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:30:48 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/23 18:34:07 by aarrien-         ###   ########.fr       */
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
		if (w[i] == NULL)
			show_error(10);
		i++;
	}
	return (0);
}

int	load_textures(t_data *data)
{
	load_n(data, data->t.p_wait, "./textures/player/wait/player_wait_", 4);
	load_n(data, data->t.p_die, "./textures/player/die/die_", 8);
	load_n(data, data->t.p_up, "./textures/player/up/player_up_", 8);
	load_n(data, data->t.p_down, "./textures/player/down/player_down_", 8);
	load_n(data, data->t.p_right, "./textures/player/right/player_right_", 8);
	load_n(data, data->t.p_left, "./textures/player/left/player_left_", 8);
	load_n(data, data->t.floor, "./textures/floor/floor_", 10);
	load_n(data, data->t.wall, "./textures/wall/wall_", 1);
	load_n(data, data->t.chest, "./textures/chest/chest_", 1);
	load_n(data, data->t.exit, "./textures/exit/exit_", 3);
	load_n(data, data->t.par, "./textures/par/par_", 8);
	load_n(data, data->t.spike, "./textures/spikes/spike_", 3);
	return (0);
}
