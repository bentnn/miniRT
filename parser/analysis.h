/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:47:03 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:47:04 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "structures.h"

t_color make_color(const char *line);
float	make_float(const char *line);
int		make_int_rt(const char *line, int max);
char	*next_nb(char *line);
int		ft_isfloat(const char *str);
int		ft_isint(const char *str);
int		ft_iscolor(const char *str);
int		ft_isvec(const char *str);
int		check_end_of_str(const char *str);
int		analysisr(t_scene *scene, const char *line);
int		analysisa(t_scene *scene, const char *line);
int		analysisc(t_scene *scene, const char *str);
int		analysisl(t_scene *scene, const char *str);
int		analysissp(t_scene *scene, const char *line);
int		analysispl(t_scene *scene, const char *line);
int		analysissq(t_scene *scene, const char *line);
int		analysiscy(t_scene *scene, const char *line);
int		analysistr(t_scene *scene, const char *line);

#endif
