/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:04:21 by aabet             #+#    #+#             */
/*   Updated: 2021/03/22 22:18:27 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <math.h>
# include "structures.h"
# include "../libft/libft.h"
# include "../vec_func/vec_func.h"
# include "fcntl.h"
# include "../main_files/mini_rt.h"

t_scene	*parser(const char *filename);
void	print_error_rt(const char *str);
int		print_error_rt_and_return(const char *str, int r);
void	ft_put_red_str(const char *str);
void	ft_put_red_str_and_n(const char *str);

#endif
