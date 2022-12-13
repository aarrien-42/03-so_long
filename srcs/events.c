/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:31:44 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/13 18:44:45 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/so_long.h"

int	controls(int keysym, t_data *data)
{
	if (keysym == 13 || keysym == 126) // w
		data->view = 1;
	if (keysym == 0 || keysym == 123) // a
		data->view = 2;
	if (keysym == 1 || keysym == 125) // s
		data->view = 3;
	if (keysym == 2 || keysym == 124) // d
		data->view = 4;
	data->moving = data->view;
	if (data->view != 0)
		data->moves++;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	printf("Keypress: %d\n", keysym);
	if (keysym == 53) // esc
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (data->moving == 0)
		controls(keysym, data);
	return (0);
}

int	handle_destroy(t_data *data)
{
	printf("Destroy\n");
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}
