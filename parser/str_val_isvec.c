/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_val_isvec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:10:26 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:10:28 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	isdig_or_minus(const char *str, int i, int *nbs, int *point)
{
	if (i == 0 || str[i - 1] == ',')
	{
		if (*point > 1)
			return (0);
		*nbs += 1;
		*point = 0;
	}
	if (str[i] == '-' && (!ft_isdigit(str[i + 1]) ||
						!(i == 0 || str[i - 1] == ',')))
		return (0);
	return (1);
}

static void	set_params(int *nbs, int *commas, int *i, int *point)
{
	*commas = 0;
	*nbs = 0;
	*i = -1;
	*point = 0;
}

int			ft_isvec(const char *str)
{
	int nbs;
	int commas;
	int i;
	int point;

	set_params(&nbs, &commas, &i, &point);
	while (str[++i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\r')
	{
		if (ft_isdigit(str[i]) || str[i] == '-')
		{
			if (!isdig_or_minus(str, i, &nbs, &point))
				return (0);
		}
		else if (str[i] == '.')
		{
			if (!ft_isdigit(str[i + 1]) || nbs == 0)
				return (0);
			point++;
		}
		else if (str[i] == ',')
			commas++;
		else
			return (0);
	}
	return (nbs == 3 && commas == 2 ? 1 : 0);
}
