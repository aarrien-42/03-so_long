/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:54:28 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/21 15:12:37 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	get_height(char *map)
{
	int		fd;
	char	*str;
	int		h;

	h = 0;
	fd = open(map, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		h++;
		free(str);
	}
	close (fd);
	return (h);
}

int	get_width(t_data *data)
{
	int	w;
	int	i;
	int	j;

	w = 0;
	i = 0;
	j = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
			i++;
		if (i > w)
			w = i;
		i = 0;
		j++;
	}
	return (w);
}

int	save_map(t_data *data, char *map, int h)
{
	int		fd;
	char	*str;
	int		i;

	data->map = malloc((h + 1) * sizeof(char *));
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while (i < h)
	{
		str = get_next_line(fd);
		if (str != NULL)
			data->map[i] = ft_strtrim(str, "\n");
		free(str);
		i++;
	}
	data->map[i] = NULL;
	close(fd);
	return (0);
}

int	print_map(t_data *data)
{
	int	i;

	i = 0;
	printf("\nMAP:\n");
	while (i < data->map_h / 32)
		printf("%s\n", data->map[i++]);
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
	int	i;

	i = 0;
	while (data->map[0][i])
		if (data->map[0][i++] == 'X')
			return(1);
	i = 0;
	while (data->map[data->map_h / 32 - 1][i])
		if (data->map[data->map_h / 32 - 1][i++] == 'X')
			return(1);
	i = 0;
	while (i < data->map_h / 32 - 1)
		if (data->map[i++][0] == 'X')
			return(1);
	i = 0;
	while (i < data->map_h / 32 - 1)
		if (data->map[i++][data->map_w / 32 - 1] == 'X')
			return(1);
	return (0);
}

int	paint_floor(t_data *data, int x, int y)
{
	char	*c;
	char	*s;

	s = "CHV0E";
	c = &data->map[y][x];
	if(*c == '0')
		*c = 'X';
	if (*c == 'E')
		return (*c = *c + 32, 0);
	if (*c == 'C' || *c == 'H' || *c == 'V')
		*c = *c + 32;
	if (y < data->map_h / 32 - 1 && ft_strchr(s, data->map[y + 1][x]) != 0)
		paint_floor(data, x, y + 1);
	if (y > 0 && data->map[y - 1][x] && ft_strchr(s, data->map[y - 1][x]) != 0)
		paint_floor(data, x, y - 1);
	if (x < data->map_w / 32 - 1 && data->map[y][x + 1] && ft_strchr(s, data->map[y][x + 1]) != 0)
		paint_floor(data, x + 1, y);
	if (x > 0 && data->map[y][x - 1] && ft_strchr(s, data->map[y][x - 1]) != 0)
		paint_floor(data, x - 1, y);
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
	pos = find(data, 'P');
	paint_floor(data, pos[0] / 32, pos[1] / 32);
	if (check_border(data) != 0)
		show_error(7);
	if (obj_count(data, 'E') != 0 || obj_count(data, 'C') != 0)
		show_error(8);
	return (0);
}
