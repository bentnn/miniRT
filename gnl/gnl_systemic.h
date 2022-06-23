/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_systemic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:33:18 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 20:33:20 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_SYSTEMIC_H
# define GNL_SYSTEMIC_H

# include <unistd.h>
# include <stdlib.h>

int	gnl_strlen(const char *str);
int	return_error(char *str1, char *str2);
int	gnl_strchr(const char *str, int c);

#endif
