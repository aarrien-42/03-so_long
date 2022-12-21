/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:09:38 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/21 16:09:59 by aarrien-         ###   ########.fr       */
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
