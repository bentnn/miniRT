/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:02:20 by aabet             #+#    #+#             */
/*   Updated: 2020/10/30 18:21:02 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) ||
			(ch >= 97 && ch <= 122))
		return (1);
	return (0);
}
