/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_tr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:49:14 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:49:16 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		n_to_tr(t_elem *elem)
{
	t_vec v0v1;
	t_vec v0v2;

	v0v1 = vec_minus(elem->coor, elem->coor2);
	v0v2 = vec_minus(elem->coor, elem->coor3);
	elem->vec = vec_norm(matrix_mult(v0v1, v0v2));
}

static void	find_neg_and_pos(t_vec abcp[3], int *neg, int *pos, t_vec v)
{
	int		i;
	float	sk;

	i = 0;
	while (i < 3)
	{
		sk = vec_dot(abcp[i++], v);
		if (sk >= 0)
			*pos += 1;
		else
			*neg += 1;
	}
}

float		intersection_tr(t_vec ray_pos, t_vec ray_dir, t_elem *current)
{
	float	t;
	t_vec	inter;
	t_vec	abcp[3];
	int		pos;
	int		neg;

	if ((t = intersection_pl(ray_pos, ray_dir, current)) <= 0)
		return (-1);
	inter = find_inter(ray_pos, ray_dir, t);
	abcp[0] = matrix_mult(vec_minus(current->coor2, current->coor),
						vec_minus(inter, current->coor));
	abcp[1] = matrix_mult(vec_minus(current->coor3, current->coor2),
						vec_minus(inter, current->coor2));
	abcp[2] = matrix_mult(vec_minus(current->coor, current->coor3),
						vec_minus(inter, current->coor3));
	pos = 0;
	neg = 0;
	find_neg_and_pos(abcp, &neg, &pos, current->vec);
	return (pos && neg ? -1 : t);
}
