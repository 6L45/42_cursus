/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:49:50 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/08 06:49:56 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	got_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	file_reader(int fd, char **line)
{
	char	*buf;
	char	*tmp;
	int		res;

	res = 1;
	buf = NULL;
	tmp = NULL;
	while (res > 0)
	{
		tmp = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		res = read(fd, tmp, BUFFER_SIZE);
		tmp[res] = '\0';
		if (got_new_line(tmp))
		{
			buf = ft_strjoin(&buf, &tmp);
			break ;
		}
		buf = ft_strjoin(&buf, &tmp);
	}
	*line = buf;
	if (res != 0)
		res = 1;
	return (res);
}

void	backup_reader(char **backup, char **line)
{
	char	*str;
	char	*ptrbu;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ptrbu = *backup;
	while (ptrbu[++i])
	{
		if (ptrbu[i] == '\n')
			break ;
	}
	str = (char *)ft_calloc((i + 1), sizeof(char));
	while (++j < i)
		str[j] = ptrbu[j];
	str[j] = '\0';
	*line = str;
	ft_strcpy(*backup, &ptrbu[i + 1]);
}

// Exactement pareil que la partie normale
// sauf que les la static est maintenant un 2D array
// qui stock les restes de lecture (après \n) array[]['ici'], 
// en fonction du FD array['la'][]
int	get_next_line(int fd, char **line)
{
	static char	backup[255][BUFFER_SIZE + 1];
	char		*transit;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL
		|| read(fd, backup[fd], 0) < 0 || fd >= 256 || fd == 1 || fd == 2)
		return (-1);
	transit = backup[fd];
	if (got_new_line(backup[fd]))
	{
		backup_reader(&transit, line);
		ft_strcpy(backup[fd], transit);
		return (1);
	}
	i = file_reader(fd, line);
	ft_strchr(line, (int) '\n', &transit);
	ft_strcpy(backup[fd], transit);
	return (i);
}
