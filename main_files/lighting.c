/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:49:50 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:49:51 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int		return_correct_color(float red, float green, float blue)
{
	blue = blue > 255 ? 255 : blue;
	green = green > 255 ? 255 : green;
	red = red > 255 ? 255 : red;
	return ((int)red * 65536 + (int)green * 256 + (int)blue);
}

static float	correct_inten(float inten,
						float inten_from_camera, t_elem *elem)
{
	if ((elem->type != 4) && ((inten < 0 && inten_from_camera < 0) ||
							(inten > 0 && inten_from_camera < 0)))
		inten *= -1;
	inten = inten > 1.0f ? 1.0f : inten;
	return (inten);
}

static float	count_inten(t_vec coor, t_vec inter, t_vec n)
{
	float inten;

	inten = vec_dot(vec_norm(vec_minus(coor, inter)), n);
	return (inten);
}

int				lighting(t_data *data, t_elem *elem, t_vec inter, t_vec n)
{
	t_fcolor	color;
	float		inten;
	float		inten_from_camera;
	t_light		*current;

	current = data->scene->light;
	color.red = (float)elem->color.red * data->scene->am_l.mult_color.red;
	color.green = (float)elem->color.green *
			data->scene->am_l.mult_color.green;
	color.blue = (float)elem->color.blue * data->scene->am_l.mult_color.blue;
	while (current)
	{
		inten = count_inten(current->coor, inter, n);
		inten_from_camera = count_inten(data->scene->camera->coor, inter, n);
		inten = correct_inten(inten, inten_from_camera, elem);
		if (inten > 0 && !has_obstacles(data, current, inter, elem->id))
		{
			color.red += inten * current->ratio * (float)current->color.red;
			color.green += inten * current->ratio *
					(float)current->color.green;
			color.blue += inten * current->ratio * (float)current->color.blue;
		}
		current = current->next;
	}
	return (return_correct_color(color.red, color.green, color.blue));
}
