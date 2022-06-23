/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:41:02 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:41:04 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_func.h"

float	vec_len(t_vec v)
{
	return (sqrtf(vec_dot(v, v)));
}

t_vec	vec_plus(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec	matrix_mult(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = -1 * (v1.x * v2.z - v1.z * v2.x);
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_vec	find_inter(t_vec ray_pos, t_vec ray_dir, float t)
{
	return (vec_plus(ray_pos, vec_mult(ray_dir, t)));
}

float	vec_cos(t_vec v1, t_vec v2)
{
	float len1;
	float len2;

	len1 = vec_len(v1);
	len2 = vec_len(v2);
	if (len1 != 0 && len2 != 0)
		return (vec_dot(v1, v2) / (len1 * len2));
	return (0);
}
