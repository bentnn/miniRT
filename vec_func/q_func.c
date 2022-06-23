/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_func.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:40:36 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:40:38 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_func.h"

t_q	create_camera_q(t_vec v)
{
	t_q		res;
	t_vec	a;
	float	len;

	a = matrix_mult(create_vec(0, 0, 1), v);
	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	res.a = 1 + vec_dot(create_vec(0, 0, 1), v);
	len = sqrtf(res.x * res.x + res.y * res.y + res.z * res.z + res.a * res.a);
	if (len != 0 && len != 1)
	{
		res.x /= len;
		res.y /= len;
		res.z /= len;
		res.a /= len;
	}
	if (v.z == -1)
		res.y = -1;
	return (res);
}

t_q	create_q(float a, float x, float y, float z)
{
	t_q res;

	res.a = a;
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_q	t_q_matrix_mult(t_q a, t_q b)
{
	t_q	res;

	res.a = a.a * b.a - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.a * b.x + a.x * b.a + a.y * b.z - a.z * b.y;
	res.y = a.a * b.y + a.y * b.a + a.z * b.x - a.x * b.z;
	res.z = a.a * b.z + a.z * b.a + a.x * b.y - a.y * b.x;
	return (res);
}

t_q	q_conj(t_q q)
{
	return (create_q(q.a, -q.x, -q.y, -q.z));
}

t_q	vec_to_q(t_vec v)
{
	t_q res;

	res.a = 0;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	return (res);
}
