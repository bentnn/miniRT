/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:50:00 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 22:50:01 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"
#include "../mlx/mlx.h"

int			hooks_win(int keycode, t_data *data)
{
	if (keycode == 48)
	{
		if (data->scene->camera && data->scene->camera_list->next)
		{
			if (data->scene->camera->next)
				data->scene->camera = data->scene->camera->next;
			else
				data->scene->camera = data->scene->camera_list;
			painting(data);
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img,
						0, 0);
		}
	}
	if (keycode == 53)
		exit(0);
	return (1);
}

int			red_button(void)
{
	exit(0);
}

static void	check_screen_size(t_data *data)
{
	int x;
	int y;

	mlx_get_screen_size(data->mlx, &x, &y);
	if (data->scene->x_size > x)
		data->scene->x_size = x;
	if (data->scene->y_size > y)
		data->scene->y_size = y;
}

static void	big_loop(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, data->scene->x_size,
								data->scene->y_size, "miniRT");
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
	mlx_hook(data->mlx_win, 2, 1L << 0, hooks_win, data);
	mlx_hook(data->mlx_win, 17, 1L << 17, red_button, data);
	mlx_loop(data->mlx);
}

int			main(int argc, char **argv)
{
	t_data *data;

	if (!(data = malloc(sizeof(t_data))))
		exit(print_error_rt_and_return("Malloc error\n", 1));
	if (argc < 2 || argc > 3)
		exit(print_error_rt_and_return("Wrong number of arguments\n", 1));
	if (argc == 3 && !is_it_save(argv[2]))
		exit(print_error_rt_and_return("invalid arguments\n", 1));
	if (!(data->scene = parser(argv[1])))
		exit(1);
	data->mlx = mlx_init();
	check_screen_size(data);
	data->mlx_img = mlx_new_image(data->mlx, data->scene->x_size,
							data->scene->y_size);
	data->addr = mlx_get_data_addr(data->mlx_img, &data->bits_per_pixel,
								&data->line_length, &data->endian);
	if (data->scene->camera)
		painting(data);
	if (argc == 2)
		big_loop(data);
	else
		exit(write_to_bmp(data, "img.bmp"));
	return (0);
}
