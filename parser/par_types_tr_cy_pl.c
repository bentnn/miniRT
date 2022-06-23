/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_types_tr_cy_pl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:52:09 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:52:11 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "analysis.h"

int		analysispl(t_scene *scene, const char *line)
{
	t_elem	*new;
	char	*str;

	if (line[0] != 'p' || line[1] != 'l' || (line[2] != ' ' && line[2] != '\t'))
		return (print_error_rt_and_return("Error in \"pl\"\n", 0));
	if (!(new = create_new_elem(scene, 1)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	str = (char*)line;
	str += 2;
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"pl\"\n", 0));
	new->coor = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"pl\"\n", 0));
	new->vec = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_iscolor(str))
		return (print_error_rt_and_return("Error in \"pl\"\n", 0));
	new->color = make_color(str);
	if (!check_end_of_str(str))
		return (print_error_rt_and_return("Extra characters in \"pl\"\n", 0));
	if (check_for_norm(new->vec) && new->color.blue >= 0)
		return (1);
	return (print_error_rt_and_return("Invalid values in \"pl\"\n", 0));
}

int		end_of_analysiscy(t_elem *new, char *str)
{
	if (!check_end_of_str(str))
		return (print_error_rt_and_return("Extra characters in \"cy\"\n", 0));
	if (check_for_norm(new->vec) && new->color.blue >= 0 &&
		new->diam > 0 && new->height > 0)
		return (1);
	return (print_error_rt_and_return("Invalid values in \"cy\"\n", 0));
}

int		analysiscy(t_scene *scene, const char *line)
{
	t_elem	*new;
	char	*str;

	if (line[0] != 'c' || line[1] != 'y' || (line[2] != ' ' && line[2] != '\t'))
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	if (!(new = create_new_elem(scene, 4)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	str = (char*)(line + 2);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	new->coor = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	new->vec = read_vec(&str);
	if (!(str = next_nb(str)) || ft_isfloat(str) != 1)
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	new->diam = make_float(str);
	if (!(str = next_nb(str)) || ft_isfloat(str) != 1)
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	new->height = make_float(str);
	if (!(str = next_nb(str)) || !ft_iscolor(str))
		return (print_error_rt_and_return("Error in \"cy\"\n", 0));
	new->color = make_color(str);
	return (end_of_analysiscy(new, str));
}

int		end_of_analysistr(t_elem *new)
{
	if (new->color.blue < 0)
		return (print_error_rt_and_return("Invalid values in \"tr\"\n", 0));
	n_to_tr(new);
	return (1);
}

int		analysistr(t_scene *scene, const char *line)
{
	t_elem	*new;
	char	*str;

	if (line[0] != 't' || line[1] != 'r' || (line[2] != ' ' && line[2] != '\t'))
		return (print_error_rt_and_return("Error in \"tr\"\n", 0));
	if (!(new = create_new_elem(scene, 5)))
		return (print_error_rt_and_return("Malloc Error\n", 0));
	str = (char*)(line + 2);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"tr\"\n", 0));
	new->coor = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"tr\"\n", 0));
	new->coor2 = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_isvec(str))
		return (print_error_rt_and_return("Error in \"tr\"\n", 0));
	new->coor3 = read_vec(&str);
	if (!(str = next_nb(str)) || !ft_iscolor(str))
		return (print_error_rt_and_return("Error in \"tr\"\n", 0));
	new->color = make_color(str);
	if (!check_end_of_str(str))
		return (print_error_rt_and_return("Extra characters in \"tr\"\n", 0));
	return (end_of_analysistr(new));
}
