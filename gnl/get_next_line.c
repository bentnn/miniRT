/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 02:01:19 by aabet             #+#    #+#             */
/*   Updated: 2020/12/24 02:14:31 by aabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "gnl_systemic.h"

static char	*str_check_and_join(char *str1, const char *str2, int fr)
{
	char	*new;
	int		size2;
	int		j;
	int		k;

	if (!str2)
		return (NULL);
	size2 = 0;
	while (str2[size2] && str2[size2] != '\n')
		size2++;
	if (!(new = malloc(sizeof(char) * (gnl_strlen(str1) + size2 + 1))))
		return (0);
	j = 0;
	k = 0;
	if (str1)
		while (str1[j])
			new[j++] = str1[k++];
	k = 0;
	while (k < size2)
		new[j++] = str2[k++];
	new[j] = '\0';
	if (fr && str1)
		free(str1);
	return (new);
}

static char	*make_residual_str(char *buf, int fr)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	j = 0;
	while (buf[j] && buf[j] != '\n')
		j++;
	if (buf[j] == '\n')
		j++;
	i = j;
	while (buf[i])
		i++;
	if (!(new = malloc(sizeof(char) * (i - j + 1))))
		return (0);
	k = 0;
	while (j < i)
		new[k++] = buf[j++];
	new[k] = '\0';
	if (fr)
		free(buf);
	return (new);
}

static int	read_from_fd(char **def, char **new, int fd, char **line)
{
	char	*buf;
	int		res;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (return_error(buf, *new));
	while ((res = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		if (res == -1)
			return (return_error(buf, 0));
		buf[res] = '\0';
		if (!(*new = str_check_and_join(*new, buf, 1)))
			return (return_error(*def, buf));
		if (gnl_strchr(buf, '\n') >= 0)
		{
			if (*def)
				free(*def);
			if (!(*def = make_residual_str(buf, 0)))
				return (return_error(*def, buf));
			free(buf);
			*line = *new;
			return (1);
		}
	}
	free(buf);
	return (0);
}

static int	have_n(char **line, char **def, char **new)
{
	if (gnl_strchr(*def, '\n') >= 0)
	{
		if (!(*def = make_residual_str(*def, 1)))
			return (return_error(*def, *new));
		*line = *new;
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*def;
	char		*new;
	int			res;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line || read(fd, 0, 0) == -1)
		return (return_error(def, 0));
	if (!(new = str_check_and_join(0, def, 0)) && def != NULL)
		return (return_error(def, 0));
	if (have_n(line, &def, &new))
		return (1);
	if ((res = read_from_fd(&def, &new, fd, line)) == 1)
		return (1);
	else if (res == -1)
		return (return_error(new, def));
	free(def);
	def = NULL;
	if (!new)
	{
		if (!(new = malloc(sizeof(char))))
			return (-1);
		new[0] = '\0';
	}
	*line = new;
	return (0);
}
