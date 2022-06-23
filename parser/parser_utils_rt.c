/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_rt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:05:10 by aabet             #+#    #+#             */
/*   Updated: 2021/03/22 22:18:50 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		make_int_rt(const char *line, int max)
{
	int res;
	int i;

	i = 0;
	res = 0;
	if (!*line)
		return (-2);
	while (ft_isdigit(*line) && i < max)
	{
		res = res * 10 + (*line - 48);
		i++;
		line++;
	}
	return (res);
}

float	make_float(const char *line)
{
	float	res;
	float	frac;
	int		minus;

	minus = 1;
	if (*line == '-')
	{
		minus = -1;
		line++;
	}
	if (*line == '-')
		return (-1);
	res = (float)make_int_rt(line, 7);
	while (ft_isdigit(*line))
		line++;
	if (*line == '.')
	{
		line++;
		frac = (float)make_int_rt(line, 7);
		while (frac >= 1)
			frac /= 10;
		res += frac;
	}
	return ((float)minus * res);
}

t_color	make_color(const char *line)
{
	t_color	res;
	char	*str;

	str = (char *)line;
	res.red = ft_atoi(str);
	while (*str != ',')
		str++;
	str++;
	res.green = ft_atoi(str);
	while (*str != ',')
		str++;
	str++;
	res.blue = ft_atoi(str);
	if (!(res.red >= 0 && res.red <= 255 &&
		res.green >= 0 && res.green <= 255 &&
		res.blue >= 0 && res.blue <= 255))
		res.blue = -1;
	return (res);
}

char	*next_nb(char *line)
{
	while (ft_isdigit(*line) || *line == '.' || *line == '-')
		line++;
	while (*line && !ft_isdigit(*line) && *line != '-')
	{
		if (*line != ' ' && *line != '\t' && *line != '\r')
			return (NULL);
		line++;
	}
	return (line);
}
