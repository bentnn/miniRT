/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:46:52 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:46:54 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float		intersection_sp(t_vec ray_pos, t_vec ray_dir, t_vec spos, float r)
{
	t_vec k;
	float b;
	float d;
	float t1;
	float t2;

	k = vec_minus(ray_pos, spos);
	b = vec_dot(k, ray_dir);
	d = b * b - (vec_dot(k, k) - r * r);
	if (d >= 0)
	{
		d = sqrtf(d);
		t1 = -b + d;
		t2 = -b - d;
		t1 = (t2 >= 0) ? t2 : t1;
		if (t1 >= 0)
			return (t1);
	}
	return (-1);
}

float		intersection_pl(t_vec ray_pos, t_vec ray_dir, t_elem *current)
{
	float t;
	float dn;

	dn = vec_dot(current->vec, ray_dir);
	if (dn != 0.0f)
	{
		t = vec_dot(vec_minus(current->coor, ray_pos), current->vec) / dn;
		if (t > 0)
			return (t);
	}
	return (-1);
}

float		intersection_sq(t_vec ray_pos, t_vec ray_dir, t_elem *current)
{
	float t;
	t_vec temp;

	if (intersection_pl(ray_pos, ray_dir, current) == -1)
		return (-1);
	t = intersection_tr(ray_pos, ray_dir, current);
	if (t <= 0)
	{
		temp = current->coor4;
		current->coor4 = current->coor2;
		current->coor2 = temp;
		t = intersection_tr(ray_pos, ray_dir, current);
		temp = current->coor4;
		current->coor4 = current->coor2;
		current->coor2 = temp;
	}
	return (t);
}

static void	n_for_cy(t_elem *cur, const float t[2], const float m[2],
					t_vec inter)
{
	cur->n = vec_norm(vec_minus(
			vec_minus(inter, cur->coor), vec_mult(cur->vec, m[0])));
	if (t[0] == t[1])
		cur->n = vec_mult(cur->n, -1);
}

float		intersection_cy(t_vec ray_pos, t_vec ray_dir, t_elem *cur)
{
	t_vec x;
	float val[5];
	float t[2];
	float m[2];

	x = vec_minus(ray_pos, cur->coor);
	val[0] = vec_dot(x, cur->vec);
	val[1] = vec_dot(ray_dir, ray_dir) - powf(vec_dot(ray_dir, cur->vec), 2);
	val[2] = 2 * (vec_dot(ray_dir, x) - vec_dot(ray_dir, cur->vec) * val[0]);
	val[3] = vec_dot(x, x) - val[0] * val[0] - (cur->diam * cur->diam / 4);
	if ((val[4] = sqrtf(val[2] * val[2] - 4 * val[1] * val[3])) < 0)
		return (-1);
	t[0] = (val[2] * -1 - val[4]) / (2 * val[1]);
	t[1] = (val[2] * -1 + val[4]) / (2 * val[1]);
	m[0] = vec_dot(ray_dir, cur->vec) * t[0] + val[0];
	m[1] = vec_dot(ray_dir, cur->vec) * t[1] + val[0];
	if (!(m[0] >= 0 && m[0] <= cur->height))
	{
		if (!(m[1] >= 0 && m[1] <= cur->height))
			return (-1);
		m[0] = m[1];
		t[0] = t[1];
	}
	n_for_cy(cur, t, m, find_inter(ray_pos, ray_dir, t[0]));
	return (t[0]);
}
