/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obstacles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:24:34 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 22:24:36 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	is_it_the_nearest(const float *ts, t_data *data, int n)
{
	int i;

	i = 0;
	while (i < n)
		if (ts[i++] < ts[data->scene->size_of_elems - 1])
			return (1);
	return (0);
}

int			has_obstacles(t_data *data, t_light *light, t_vec inter, int id)
{
	float	t;
	float	ts[data->scene->size_of_elems];
	int		n;
	t_elem	*current;
	t_vec	ray_dir;

	n = 0;
	current = data->scene->elems;
	ray_dir = vec_norm(vec_minus(inter, light->coor));
	while (current)
	{
		t = find_t(light->coor, ray_dir, current);
		if (current->id == id)
			ts[data->scene->size_of_elems - 1] = t;
		else if (t > 0)
			ts[n++] = t;
		current = current->next;
	}
	return (is_it_the_nearest(ts, data, n));
}
