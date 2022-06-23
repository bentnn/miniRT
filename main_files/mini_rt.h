/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:22:31 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 22:22:33 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <fcntl.h>
# include "../vec_func/vec_func.h"
# include "../parser/structures.h"
# include "math.h"

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40

float	intersection_sp(t_vec ray_pos, t_vec ray_dir, t_vec spos, float r);
float	intersection_pl(t_vec ray_pos, t_vec ray_dir, t_elem *current);
float	intersection_tr(t_vec ray_pos, t_vec ray_dir, t_elem *current);
float	intersection_cy(t_vec ray_pos, t_vec ray_dir, t_elem *cur);
float	intersection_sq(t_vec ray_pos, t_vec ray_dir, t_elem *current);
void	n_to_tr(t_elem *elem);
void	painting(t_data *data);
int		which_color_put(t_data *data, t_vec ray_pos, t_vec ray_dir);
int		lighting(t_data *data, t_elem *elem, t_vec inter, t_vec n);
float	find_t(t_vec ray_pos, t_vec ray_dir, t_elem *current);
int		has_obstacles(t_data *data, t_light *light, t_vec inter, int id);
int		is_it_save(const char *s);
int		write_to_bmp(t_data *data, char *filename);

#endif
