/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:10:59 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:11:00 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isfloat(const char *str)
{
	char	*s;
	int		res;
	int		point;

	s = (char *)str;
	res = s[0] == '-' ? -1 : 1;
	if (s[0] == '-')
		s++;
	point = 0;
	while (*s && *s != ' ' && *s != '\t')
	{
		if (ft_isdigit(*s) || *s == '.')
		{
			if (*s == '.')
			{
				if (!ft_isdigit(*(s + 1)))
					return (0);
				point++;
			}
			s++;
		}
		else
			return (0);
	}
	return (point <= 1 ? res : 0);
}

int	ft_isint(const char *str)
{
	char	*s;
	int		res;

	s = (char *)str;
	res = s[0] == '-' ? -1 : 1;
	if (s[0] == '-')
		s++;
	while (*s && *s != ' ' && *s != '\t' && *s != '\r')
	{
		if (ft_isdigit(*s))
			s++;
		else
			return (0);
	}
	return (res);
}

int	ft_iscolor(const char *str)
{
	int	commas;
	int	nbs;
	int	i;

	commas = 0;
	nbs = 0;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\r')
	{
		if (ft_isdigit(str[i]))
		{
			if (i == 0 || str[i - 1] == ',')
				nbs++;
		}
		else if (str[i] == ',')
			commas++;
		else
			return (0);
		i++;
	}
	if (commas == 2 && nbs == 3)
		return (1);
	return (0);
}

int	check_end_of_str(const char *str)
{
	while (*str && (ft_isdigit(*str) || *str == '.' || *str == '-' ||
			*str == ','))
		str++;
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}
