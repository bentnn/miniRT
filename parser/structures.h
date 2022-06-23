/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:11:56 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:11:58 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_q
{
	float			a;
	float			x;
	float			y;
	float			z;
}					t_q;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct		s_fcolor
{
	float			red;
	float			green;
	float			blue;
}					t_fcolor;

typedef struct		s_camera
{
	t_vec			coor;
	t_vec			vec;
	t_q				rot;
	int				fov;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_light
{
	t_vec			coor;
	float			ratio;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_amb_light
{
	float			ratio;
	t_color			color;
	t_fcolor		mult_color;
}					t_amb_light;

typedef struct		s_elem
{
	int				type;
	int				id;
	t_vec			coor;
	t_vec			coor2;
	t_vec			coor3;
	t_vec			coor4;
	t_vec			vec;
	t_vec			n;
	float			diam;
	float			height;
	t_color			color;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_scene
{
	int				x_size;
	int				y_size;
	t_amb_light		am_l;
	t_camera		*camera;
	t_camera		*camera_list;
	t_light			*light;
	t_elem			*elems;
	int				size_of_elems;
}					t_scene;

typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_scene			*scene;
}					t_data;

typedef struct		s_intersection
{
	float			t;
	t_elem			*elem;
}					t_intersection;

t_scene				*create_new_scene();
void				delete_scene(t_scene *scene);
t_camera			*create_new_camera(t_scene *scene);
t_light				*create_new_light(t_scene *scene);
t_elem				*create_new_elem(t_scene *scene, int type);

#endif
