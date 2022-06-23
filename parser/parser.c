/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:15:24 by aabet             #+#    #+#             */
/*   Updated: 2021/03/18 21:15:26 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "analysis.h"
#include "../gnl/get_next_line.h"

static int		analysis(t_scene *scene, const char *line)
{
	char *s;

	if (line[0] == '\0' || line[0] == '\n' || line[0] == '\r')
		return (1);
	if (ft_strchr(line, 'R'))
		return (analysisr(scene, line));
	if (ft_strchr(line, 'A'))
		return (analysisa(scene, line));
	if (ft_strchr(line, 'c') && !ft_strchr(line, 'y'))
		return (analysisc(scene, line));
	if (ft_strchr(line, 'l') && !ft_strchr(line, 'p'))
		return (analysisl(scene, line));
	if ((s = ft_strchr(line, 's')) && *(s + 1) == 'p')
		return (analysissp(scene, line));
	if ((s = ft_strchr(line, 'p')) && *(s + 1) == 'l')
		return (analysispl(scene, line));
	if ((s = ft_strchr(line, 's')) && *(s + 1) == 'q')
		return (analysissq(scene, line));
	if ((s = ft_strchr(line, 'c')) && *(s + 1) == 'y')
		return (analysiscy(scene, line));
	if ((s = ft_strchr(line, 't')) && *(s + 1) == 'r')
		return (analysistr(scene, line));
	print_error_rt("Invalid element type in string:\n");
	ft_put_red_str_and_n(line);
	return (0);
}

static int		check_parser_er(const char *filename, t_scene **scene)
{
	int fd;
	int size;

	size = (int)ft_strlen(filename);
	if (!(filename[size - 1] == 't' && filename[size - 2] == 'r' &&
			filename[size - 3] == '.'))
	{
		print_error_rt("File must be .rt\n");
		return (0);
	}
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		print_error_rt("The file can not be opened for reading\n");
		return (0);
	}
	if (!(*scene = create_new_scene()))
	{
		print_error_rt("Malloc error\n");
		close(fd);
		return (0);
	}
	return (fd);
}

static t_scene	*parser_has_error(int fd, int res)
{
	close(fd);
	if (res == -1)
		print_error_rt("Read error\n");
	exit(1);
}

static t_scene	*end_of_parser(t_scene *scene, int fd)
{
	t_elem	*current;
	int		res;

	if (scene->y_size == 0 || scene->am_l.ratio == -1)
	{
		close(fd);
		print_error_rt("R and A are required parameters\n");
		exit(1);
	}
	res = 0;
	current = scene->elems;
	while (current)
	{
		current->id = res;
		res++;
		current = current->next;
	}
	scene->size_of_elems = res;
	scene->camera_list = scene->camera;
	close(fd);
	return (scene);
}

t_scene			*parser(const char *filename)
{
	t_scene	*scene;
	int		res;
	int		fd;
	char	*line;

	if (!(fd = check_parser_er(filename, &scene)))
		return (NULL);
	while (1)
	{
		res = get_next_line(fd, &line);
		if (res == -1 || !analysis(scene, line))
			parser_has_error(fd, res);
		free(line);
		line = NULL;
		if (res == 0)
			return (end_of_parser(scene, fd));
	}
}
