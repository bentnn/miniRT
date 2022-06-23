/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func_rt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:49:08 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:49:10 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_putstr(const char *str)
{
	if (str)
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
}

void		ft_put_red_str(const char *str)
{
	ft_putstr("\x1b[31m");
	ft_putstr(str);
	ft_putstr("\x1b[0m");
}

void		print_error_rt(const char *str)
{
	ft_put_red_str("Error\n");
	ft_put_red_str(str);
}

int			print_error_rt_and_return(const char *str, int r)
{
	print_error_rt(str);
	return (r);
}

void		ft_put_red_str_and_n(const char *str)
{
	ft_putstr("\x1b[31m");
	ft_putstr(str);
	ft_putstr("\x1b[0m");
	ft_putstr("\n");
}
