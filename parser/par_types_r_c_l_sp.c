/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_types_r_c_l_sp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:51:58 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:52:00 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "analysis.h"

int		ret_an_r(t_scene *scene)
{
	return (scene->y_size > 0 && scene->x_size > 0 ? 1 :
			print_error_rt_and_return("Invalid values in \"R\"\n", 0));
}

int		analysisr(t_scene *scene, const char *line)
{
	if (scene->x_size)
		return (print_error_rt_and_return("A lot of \"R\"\n", 0));
	if (line[0] != 'R' || (line[1] != ' ' && line[1] != '\t'))
		return (print_error_rt_and_return("Error in \"R\"\n", 0));
	while (*line)
	{
		line++;
		if (ft_isdigit(*line))
		{
			if (ft_isint(line) != 1)
				return (print_error_rt_and_return("All numbers in \"R\" "
									"must be positive int\n", 0));
			else if (!scene->x_size)
				scene->x_size = make_int_rt(line, 6);
			else if (!scene->y_size)
				scene->y_size = make_int_rt(line, 6);
			else
				return (print_error_rt_and_return("Error in \"R\"\n", 0));
			while (*line && ft_isdigit(*line))
				line++;
		}
		else if (*line && *line != ' ' && *line != '\t' && *line != '\r')
			return (print_error_rt_and_return("Error in \"R\"\n", 0));
	}
	return (ret_an_r(scene));
}

int		analysisc(t_scene *scene, const char *str)
{
	t_camera	*cur;
	char		*line;

	if (str[0] != 'c' || (str[1] != ' ' && str[1] != '\t'))
		return (print_error_rt_and_return("Error in \"c\"\n", 0));
	if (!(cur = create_new_camera(scene)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	line = (char*)str;
	line++;
	if (!(line = next_nb(line)) || !ft_isvec(line))
		return (print_error_rt_and_return("Error in \"c\"\n", 0));
	cur->coor = read_vec(&line);
	if (!(line = next_nb(line)) || !ft_isvec(line))
		return (print_error_rt_and_return("Error in \"c\"\n", 0));
	cur->vec = read_vec(&line);
	if (!(line = next_nb(line)) || ft_isint(line) != 1)
		return (print_error_rt_and_return("Error in \"c\"\n", 0));
	cur->fov = make_int_rt(line, 4);
	if (!check_end_of_str(line))
		return (print_error_rt_and_return("Extra characters in \"c\"\n", 0));
	if (!(check_for_norm(cur->vec) && cur->fov >= 0 && cur->fov <= 180))
		return (print_error_rt_and_return("Invalid values in \"c\"\n", 0));
	cur->rot = create_camera_q(cur->vec);
	return (1);
}

int		analysisl(t_scene *scene, const char *str)
{
	t_light	*cur;
	char	*line;

	if (str[0] != 'l' || (str[1] != ' ' && str[1] != '\t'))
		return (print_error_rt_and_return("Error in \"l\"\n", 0));
	if (!(cur = create_new_light(scene)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	line = (char *)str;
	line++;
	if (!(line = next_nb(line)) || !ft_isvec(line))
		return (print_error_rt_and_return("Error in \"l\"\n", 0));
	cur->coor = read_vec(&line);
	if (!(line = next_nb(line)) || ft_isfloat(line) != 1)
		return (print_error_rt_and_return("Error in \"l\"\n", 0));
	cur->ratio = make_float(line);
	if (!(line = next_nb(line)) || !ft_iscolor(line))
		return (print_error_rt_and_return("Error in \"l\"\n", 0));
	cur->color = make_color(line);
	if (!check_end_of_str(line))
		return (print_error_rt_and_return("Extra characters in \"l\"\n", 0));
	if (cur->ratio >= 0 && cur->ratio <= 1 && cur->color.blue >= 0)
		return (1);
	return (print_error_rt_and_return("Invalid values in \"l\"\n", 0));
}

int		analysissp(t_scene *scene, const char *line)
{
	t_elem	*new;
	char	*str;

	if (line[0] != 's' || line[1] != 'p' || (line[2] != ' ' && line[2] != '\t'))
		return (print_error_rt_and_return("Error in \"sp\"\n", 0));
	if (!(new = create_new_elem(scene, 2)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	str = (char*)line;
	str += 2;
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"sp\"\n", 0));
	new->coor = read_vec(&str);
	if (!(str = next_nb(str)) || ft_isfloat(str) != 1)
		return (print_error_rt_and_return("Error in \"sp\"\n", 0));
	new->diam = make_float(str);
	if (!(str = next_nb(str)) || !ft_iscolor(str))
		return (print_error_rt_and_return("Error in \"sp\"\n", 0));
	new->color = make_color(str);
	if (!check_end_of_str(str))
		return (print_error_rt_and_return("Extra characters in \"sp\"\n", 0));
	if (new->diam > 0 && new->color.blue >= 0)
		return (1);
	return (print_error_rt_and_return("Invalid values in \"sp\"\n", 0));
}
