/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_color_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:44:46 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 22:44:47 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float		find_t(t_vec ray_pos, t_vec ray_dir, t_elem *current)
{
	if (current->type == 2)
		return (intersection_sp(ray_pos, ray_dir, current->coor,
						current->diam / 2));
	else if (current->type == 1)
		return (intersection_pl(ray_pos, ray_dir, current));
	else if (current->type == 5)
		return (intersection_tr(ray_pos, ray_dir, current));
	else if (current->type == 4)
		return (intersection_cy(ray_pos, ray_dir, current));
	else if (current->type == 3)
		return (intersection_sq(ray_pos, ray_dir, current));
	return (-1);
}

static int	find_min(t_intersection *inter, int n)
{
	int i;
	int min;

	if (n == 0)
		return (-1);
	i = 0;
	min = 0;
	while (i < n)
	{
		if ((inter + i)->t < (inter + min)->t)
			min = i;
		i++;
	}
	return (min);
}

static int	find_color(t_intersection *inter, int min,
					t_vec intersec, t_data *data)
{
	if (min == -1)
		return (0);
	if ((inter + min)->t > 0)
	{
		if ((inter + min)->elem->type % 2 == 0)
		{
			if ((inter + min)->elem->type == 2)
				(inter + min)->elem->n = vec_norm(vec_minus(intersec,
												(inter + min)->elem->coor));
			return (lighting(data, (inter + min)->elem, intersec,
					(inter + min)->elem->n));
		}
		else
			return (lighting(data, (inter + min)->elem, intersec,
					(inter + min)->elem->vec));
	}
	return (0);
}

int			which_color_put(t_data *data, t_vec ray_pos, t_vec ray_dir)
{
	t_intersection	inter[data->scene->size_of_elems];
	t_elem			*current;
	int				n;
	int				min;

	if (!data->scene->elems)
		return (0);
	n = 0;
	current = data->scene->elems;
	while (current)
	{
		(inter + n)->t = find_t(ray_pos, ray_dir, current);
		if ((inter + n)->t > 1)
		{
			(inter + n)->elem = current;
			n++;
		}
		current = current->next;
	}
	min = find_min(inter, n);
	return (find_color(inter, min, find_inter(ray_pos, ray_dir,
										(inter + min)->t), data));
}
