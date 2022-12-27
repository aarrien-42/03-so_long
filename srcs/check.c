/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:54:28 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/27 16:04:46 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	check_rect(t_data *data)
{
	int		i;
	size_t	len;

	i = 1;
	len = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		if (len != ft_strlen(data->map[i]))
			return (1);
		i++;
	}
	if (i == 1)
		return (1);
	return (0);
}

int	check_border(t_data *data)
{
	int		i;
	char	*s;

	i = 0;
	s = "XchvP0";
	while (data->map[0][i])
		if (ft_strchr(s, data->map[0][i++]) != 0)
			return (1);
	i = 0;
	while (data->map[data->map_h / 32 - 1][i])
		if (ft_strchr(s, data->map[data->map_h / 32 - 1][i++]) != 0)
			return (1);
	i = 0;
	while (i < data->map_h / 32 - 1)
		if (ft_strchr(s, data->map[i++][0]) != 0)
			return (1);
	i = 0;
	while (i < data->map_h / 32 - 1)
		if (ft_strchr(s, data->map[i++][data->map_w / 32 - 1]) != 0)
			return (1);
	return (0);
}

int	paint_floor(t_data *data, int x, int y)
{
	char	*c;
	char	*s;

	s = "CHV0E";
	c = &data->map[y][x];
	if (*c == '0')
		*c = 'X';
	if (*c == 'E')
		return (*c = *c + 32, 0);
	if (*c == 'C' || *c == 'H' || *c == 'V')
		*c = *c + 32;
	if (y < data->map_h / 32 - 1 && ft_strchr(s, data->map[y + 1][x]) != 0)
		paint_floor(data, x, y + 1);
	if (y > 0 && data->map[y - 1][x] && ft_strchr(s, data->map[y - 1][x]) != 0)
		paint_floor(data, x, y - 1);
	if (x < data->map_w / 32 - 1 && data->map[y][x + 1] &&
		ft_strchr(s, data->map[y][x + 1]) != 0)
		paint_floor(data, x + 1, y);
	if (x > 0 && data->map[y][x - 1] && ft_strchr(s, data->map[y][x - 1]) != 0)
		paint_floor(data, x - 1, y);
	return (0);
}

int	check_valid_letters(t_data *data)
{
	int		i;
	int		j;
	char	*valid;

	i = 0;
	j = 0;
	valid = "01PECHV";
	while (j < (data->map_h / 32))
	{
		while (i < (data->map_w / 32))
		{
			if (ft_strchr(valid, data->map[j][i]) == 0)
				return (1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	check_map(t_data *data, char *input)
{
	int	*pos;

	if (ft_strncmp(".ber", &input[ft_strlen(input) - 4], 4) != 0)
		show_error(1);
	data->map_h = get_height(input) * 32;
	if (save_map(data, input, data->map_h / 32) != 0)
		show_error(2);
	data->map_w = get_width(data) * 32;
	if (obj_count(data, 'C') < 1)
		show_error(3);
	if (obj_count(data, 'P') != 1)
		show_error(4);
	if (obj_count(data, 'E') != 1)
		show_error(5);
	if (check_rect(data) != 0)
		show_error(6);
	if (check_valid_letters(data) != 0)
		show_error(7);
	pos = find(data, 'P');
	paint_floor(data, pos[0] / 32, pos[1] / 32);
	if (check_border(data) != 0)
		show_error(8);
	if (obj_count(data, 'E') != 0 || obj_count(data, 'C') != 0)
		show_error(9);
	return (0);
}
