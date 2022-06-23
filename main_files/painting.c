/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:25:00 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 22:25:02 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static t_vec	find_point_on_screen(t_data *data)
{
	t_vec cor;

	if (data->scene->camera->fov != 180)
		cor.z = (float)data->scene->x_size /
			(2 * tanf((float)data->scene->camera->fov / 114.5916f));
	else
		cor.z = 0.001f;
	cor.x = -1 * (float)data->scene->x_size / 2;
	cor.y = (float)data->scene->y_size / 2;
	return (cor);
}

void			painting(t_data *data)
{
	t_vec	cor;
	t_vec	ray_dir;
	int		w;
	int		h;

	cor = find_point_on_screen(data);
	w = 0;
	while (w < data->scene->x_size)
	{
		h = 0;
		while (h < data->scene->y_size)
		{
			ray_dir.x = cor.x + (float)w;
			ray_dir.z = cor.z;
			ray_dir.y = cor.y - (float)h;
			ray_dir = vec_norm(ray_dir);
			ray_dir = q_to_vec(q_rotate(data->scene->camera->rot, ray_dir));
			my_mlx_pixel_put(data, w, h,
					which_color_put(data, data->scene->camera->coor, ray_dir));
			h++;
		}
		w++;
	}
}
