/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:40:56 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:40:57 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_FUNC_H
# define VEC_FUNC_H

# include "../main_files/mini_rt.h"
# include "../parser/structures.h"

t_vec	create_vec(float x, float y, float z);
float	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_norm(t_vec v);
t_vec	vec_minus(t_vec v1, t_vec v2);
t_vec	vec_mult(t_vec v, float ch);
float	vec_len(t_vec v);
t_vec	vec_plus(t_vec v1, t_vec v2);
t_vec	matrix_mult(t_vec v1, t_vec v2);
t_vec	find_inter(t_vec ray_pos, t_vec ray_dir, float t);
float	vec_cos(t_vec v1, t_vec v2);
t_vec	find_n_to_vec(t_vec v);
int		check_for_norm(t_vec v);
t_vec	read_vec(char **line);
t_vec	full_vec(float ch);
t_color	full_color(int ch);

t_q		t_q_matrix_mult(t_q a, t_q b);
t_q		q_conj(t_q q);
t_q		vec_to_q(t_vec v);
t_vec	q_to_vec(t_q v);
t_q		q_rotate(t_q rot, t_vec t);
t_q		create_camera_q(t_vec v);

#endif
