/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:42:02 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:42:04 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "../parser/parser.h"

int			is_it_save(const char *s)
{
	int		i;
	char	*str;

	str = "--save";
	if (ft_strlen(s) != 6)
		return (0);
	i = 0;
	while (i < 6)
	{
		if (s[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

static int	bmp_f_header(t_data *data, int padding_size, int fd)
{
	unsigned char	*f_header;
	int				f_size;

	if (!(f_header = ft_calloc(BMP_FILE_HEADER_SIZE, sizeof(unsigned char))))
	{
		print_error_rt("Malloc Error\n");
		close(fd);
		return (0);
	}
	f_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE
			+ (data->bits_per_pixel / 8 * data->scene->x_size + padding_size)
			* data->scene->y_size;
	f_header[0] = (unsigned char)('B');
	f_header[1] = (unsigned char)('M');
	f_header[2] = (unsigned char)(f_size);
	f_header[3] = (unsigned char)(f_size >> 8);
	f_header[4] = (unsigned char)(f_size >> 16);
	f_header[5] = (unsigned char)(f_size >> 24);
	f_header[10] = (unsigned char)(BMP_FILE_HEADER_SIZE
								+ BMP_INFO_HEADER_SIZE);
	write(fd, f_header, BMP_FILE_HEADER_SIZE);
	free(f_header);
	return (1);
}

static int	bmp_i_header(t_data *data, int fd)
{
	unsigned char	*i_header;

	if (!(i_header = ft_calloc(BMP_INFO_HEADER_SIZE, sizeof(unsigned char))))
	{
		print_error_rt("Malloc Error\n");
		close(fd);
		return (0);
	}
	i_header[0] = (unsigned char)(40);
	i_header[4] = (unsigned char)(data->scene->x_size);
	i_header[5] = (unsigned char)(data->scene->x_size >> 8);
	i_header[6] = (unsigned char)(data->scene->x_size >> 16);
	i_header[7] = (unsigned char)(data->scene->x_size >> 24);
	i_header[8] = (unsigned char)(data->scene->y_size);
	i_header[9] = (unsigned char)(data->scene->y_size >> 8);
	i_header[10] = (unsigned char)(data->scene->y_size >> 16);
	i_header[11] = (unsigned char)(data->scene->y_size >> 24);
	i_header[12] = (unsigned char)(1);
	i_header[14] = (unsigned char)(data->bits_per_pixel);
	write(fd, i_header, BMP_INFO_HEADER_SIZE);
	free(i_header);
	return (1);
}

int			write_to_bmp(t_data *data, char *filename)
{
	int	fd;
	int	padding_size;
	int h;
	int w;

	if (!(fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		return (print_error_rt_and_return("The file can not be opened\n", 1));
	padding_size = (4 - (data->scene->x_size * data->bits_per_pixel / 8) % 4)
			% 4;
	if (!bmp_f_header(data, padding_size, fd) || !bmp_i_header(data, fd))
		return (1);
	h = data->scene->y_size;
	while (h--)
	{
		w = 0;
		while (w < data->scene->x_size)
		{
			write(fd, data->addr + (h * data->line_length +
				w * data->bits_per_pixel / 8), 4);
			w++;
		}
	}
	close(fd);
	return (0);
}
