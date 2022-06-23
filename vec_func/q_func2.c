/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_func2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:40:43 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:40:44 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_func.h"

t_vec	q_to_vec(t_q v)
{
	t_vec res;

	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	return (res);
}

t_q		q_rotate(t_q rot, t_vec t)
{
	return (t_q_matrix_mult(t_q_matrix_mult(rot, vec_to_q(t)), q_conj(rot)));
}
