/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:54:28 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/19 19:21:03 by aarrien-         ###   ########.fr       */
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
	int	i;
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

int	check_path(t_data *data)
{
	char	**tmp_map;
	int		s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = 0;
	tmp_map = malloc((data->map_h + 1) * sizeof(char *));
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (s == 0 && data->map[j][i] == 0)
			{
				s = 1;
			}
			if (s == 1)
			{
				//if (data->map[j][i] == 0)
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

int	check_map(t_data *data, char *input)
{
	data->map_h = get_height(input) * 32;
	save_map(data, input, data->map_h / 32);
	data->map_w = get_width(data) * 32;
	if (obj_count(data, 'C') < 1)
		return (1);
	if (obj_count(data, 'E') != 1 || obj_count(data, 'P') != 1)
		return (2);
	if (check_rect(data) != 0)
		return (3);
	//if (check_path(data) != 0)
	//	return (4);
	//print_map(data);
	return (0);
}
