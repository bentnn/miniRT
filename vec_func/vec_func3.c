/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_func3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:41:14 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:41:15 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_func.h"
#include "../parser/analysis.h"
#include "../libft/libft.h"

t_vec	find_n_to_vec(t_vec v)
{
	t_vec	res;
	int		not_zero;

	not_zero = (int)(v.x / v.x + v.y / v.y + v.z / v.z);
	if (not_zero == 3)
		res = create_vec(-v.y, v.x, 0);
	else
	{
		if (v.z == 0)
			res = create_vec(0, 0, 1);
		else if (v.y == 0)
			res = create_vec(0, 1, 0);
		else
			res = create_vec(1, 0, 0);
	}
	return (res);
}

int		check_for_norm(t_vec v)
{
	float len;

	len = vec_len(v);
	if (len >= 0.99 && len <= 1.01)
		return (1);
	return (0);
}

t_vec	read_vec(char **line)
{
	char	*str;
	t_vec	v;

	str = (char *)*line;
	v.x = make_float(str);
	while (*str != ',')
		str++;
	str++;
	v.y = make_float(str);
	while (*str != ',')
		str++;
	str++;
	v.z = make_float(str);
	while (ft_isdigit(*str) || *str == '.')
		str++;
	*line = str;
	return (v);
}

t_vec	full_vec(float ch)
{
	t_vec new;

	new.x = ch;
	new.y = ch;
	new.z = ch;
	return (new);
}

t_color	full_color(int ch)
{
	t_color new;

	new.blue = ch;
	new.green = ch;
	new.red = ch;
	return (new);
}
