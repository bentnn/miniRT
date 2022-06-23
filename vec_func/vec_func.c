/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:40:49 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:40:50 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_func.h"

t_vec	create_vec(float x, float y, float z)
{
	t_vec res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

float	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_norm(t_vec v)
{
	t_vec	norm;
	float	len;

	len = vec_len(v);
	if (len == 0 || len == 1)
		return (v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

t_vec	vec_minus(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec	vec_mult(t_vec v, float ch)
{
	t_vec res;

	res.x = v.x * ch;
	res.y = v.y * ch;
	res.z = v.z * ch;
	return (res);
}
