/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:16:45 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/23 14:08:17 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	show_info(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 5, 15, 0x00FFFFFF, "MOVES:");
	mlx_string_put(data->mlx, data->win, 50, 15, 0x00FFFFFF,
		ft_itoa(data->moves));
	mlx_string_put(data->mlx, data->win, 5, 30, 0x00FFFFFF, "CHESTS:");
	mlx_string_put(data->mlx, data->win, 60, 30, 0x00FFFFFF,
		ft_itoa(data->chests_init - obj_count(data, 'c')));
	mlx_string_put(data->mlx, data->win, 75, 30, 0x00FFFFFF, "of");
	mlx_string_put(data->mlx, data->win, 95, 30, 0x00FFFFFF,
		ft_itoa(data->chests_init));
	return (0);
}

void	show_error(int code)
{
	ft_putstr_fd("Error\n", 2);
	if (code == 0)
		ft_putstr_fd("Invalid input\n", 2);
	if (code == 1)
		ft_putstr_fd("Invalid file\n", 2);
	if (code == 2)
		ft_putstr_fd("Unable to read from the file\n", 2);
	if (code == 3)
		ft_putstr_fd("Invalid characters in map\n", 2);
	if (code == 4)
		ft_putstr_fd("Not a single collectable\n", 2);
	if (code == 5)
		ft_putstr_fd("Invalid number of players\n", 2);
	if (code == 6)
		ft_putstr_fd("Invalid number of exits\n", 2);
	if (code == 7)
		ft_putstr_fd("The map is not a rectangle\n", 2);
	if (code == 8)
		ft_putstr_fd("The map is not fully closed\n", 2);
	if (code == 9)
		ft_putstr_fd("Imposible map\n", 2);
	exit(0);
}

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

int	obj_count(t_data *data, char c)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (data->map[j][i] == c)
				count++;
			i++;
		}
		i = 0;
		j++;
	}
	return (count);
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
