/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_types_a_sq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:49:52 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:49:53 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "analysis.h"

static void	create_mc_for_a(t_scene *scene)
{
	scene->am_l.mult_color.red = scene->am_l.ratio *
			(float)scene->am_l.color.red / 255;
	scene->am_l.mult_color.green = scene->am_l.ratio *
			(float)scene->am_l.color.green / 255;
	scene->am_l.mult_color.blue = scene->am_l.ratio *
			(float)scene->am_l.color.blue / 255;
}

static int	analysisa_isdigit(t_scene *scene, const char *line)
{
	if (scene->am_l.ratio == -1)
	{
		if (ft_isfloat(line) != 1)
			return (print_error_rt_and_return("Error in \"A\"\n", 0));
		scene->am_l.ratio = make_float(line);
	}
	else if (scene->am_l.color.blue == -1)
	{
		if (!ft_iscolor(line))
			return (print_error_rt_and_return("Error in \"A\"\n", 0));
		scene->am_l.color = make_color(line);
	}
	else
		return (print_error_rt_and_return("Error in \"A\"\n", 0));
	return (1);
}

int			analysisa(t_scene *scene, const char *line)
{
	if (scene->am_l.ratio >= 0)
		return (print_error_rt_and_return("A lot of \"A\"\n", 0));
	if (line[0] != 'A' || (line[1] != ' ' && line[1] != '\t'))
		return (print_error_rt_and_return("Error in \"A\"\n", 0));
	while (*(++line))
	{
		if (ft_isdigit(*line))
		{
			if (!analysisa_isdigit(scene, line))
				return (0);
			while (ft_isdigit(*line) || *line == '.' || *line == ',')
				line++;
			line--;
		}
		else if (*line != ' ' && *line != '\t' && *line != '\r')
			return (print_error_rt_and_return(
					"Extra characters in \"A\"\n", 0));
	}
	if (!(scene->am_l.ratio >= 0.0 && scene->am_l.ratio <= 1.0 &&
		scene->am_l.color.blue >= 0))
		return (print_error_rt_and_return("Invalid values in \"A\"\n", 0));
	create_mc_for_a(scene);
	return (1);
}

static int	coor_for_sq(t_elem *elem)
{
	t_vec	v;
	float	diag;

	v = vec_norm(find_n_to_vec(elem->vec));
	diag = sqrtf(2) * elem->height / 2;
	elem->coor2 = vec_plus(elem->coor, vec_mult(v, diag));
	v = vec_norm(matrix_mult(elem->vec, v));
	elem->coor3 = vec_plus(elem->coor, vec_mult(v, diag));
	v = vec_norm(matrix_mult(elem->vec, v));
	elem->coor4 = vec_plus(elem->coor, vec_mult(v, diag));
	v = vec_norm(matrix_mult(elem->vec, v));
	elem->coor = vec_plus(elem->coor, vec_mult(v, diag));
	return (1);
}

int			analysissq(t_scene *scene, const char *line)
{
	t_elem	*new;
	char	*str;

	if (line[0] != 's' || line[1] != 'q' || (line[2] != ' ' && line[2] != '\t'))
		return (print_error_rt_and_return("Error in \"sq\"\n", 0));
	if (!(new = create_new_elem(scene, 3)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	str = (char*)(line + 2);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"sq\"\n", 0));
	new->coor = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"sq\"\n", 0));
	new->vec = read_vec(&str);
	if (!(str = next_nb(str)) || ft_isfloat(str) != 1)
		return (print_error_rt_and_return("Error in \"sq\"\n", 0));
	new->height = make_float(str);
	if (!(str = next_nb(str)) || !ft_iscolor(str))
		return (print_error_rt_and_return("Error in \"sq\"\n", 0));
	new->color = make_color(str);
	if (!check_end_of_str(str))
		return (print_error_rt_and_return("Extra characters in \"sq\"\n", 0));
	if (!(check_for_norm(new->vec) && new->height > 0 && new->color.blue >= 0))
		return (print_error_rt_and_return("Invalid values in \"sq\"\n", 0));
	return (coor_for_sq(new));
}
