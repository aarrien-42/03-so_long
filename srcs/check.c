/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:54:28 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/14 12:03:13 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	get_height(char *map)
{
	int		fd;
	char	c;
	int		h;

	h = 0;
	fd = open(map, O_RDONLY);
	while (read(fd, &c, 1))
		if (c == '\n')
			h++;
	close (fd);
	return (h + 1);
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
	return (w - 1);
}

int	save_map(t_data *data, char *map, int h)
{
	int	fd;
	int	i;

	data->map = malloc((h + 1) * sizeof(char *));
	fd = open(map, O_RDONLY);
	free(map);
	i = 0;
	while (i < h)
		data->map[i++] = get_next_line(fd);
	data->map[i] = NULL;
	close(fd);
	return (0);
}

int	print_map(t_data *data)
{
	int	i;

	i = 0;
	printf("MAP:\n");
	while (i < data->map_h / 32)
		printf("%s", data->map[i++]);
	return (0);
}

int	check_map(t_data *data, char *input)
{
	char	*map;

	map = ft_strjoin("maps/", input);
	data->map_h = get_height(map) * 32;
	save_map(data, map, data->map_h / 32);
	data->map_w = get_width(data) * 32;
	print_map(data);
	return (0);
}
