/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:51:53 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:51:54 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*str_char_cat(char *buf, char c)
{
	size_t	buflen;
	char	*str;
	size_t	i;

	i = 0;
	buflen = ft_strlen(buf);
	str = (char *)ft_calloc((buflen + 2), sizeof(char));
	while (i < buflen)
	{
		str[i] = buf[i];
		i++;
	}
	str[buflen] = c;
	str[buflen + 1] = '\0';
	free(buf);
	return (str);
}

void	map_creation_from_buf(char ***map, char *buf, int n)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			(*map)[j][k] = '\0';
			i++;
			j++;
			k = 0;
		}
		(*map)[j][k] = buf[i];
		i++;
		k++;
	}
	(*map)[n + 1] = NULL;
}

char	**map_to_tab(char *buf, int lanesize, int n)
{
	int		i;
	char	**map;

	i = 0;
	map = (char **)ft_calloc((n + 2), sizeof(char *));
	while (i <= n)
		map[i++] = (char *)ft_calloc((lanesize + 1), sizeof(char));
	map_creation_from_buf(&map, buf, n);
	return (map);
}

char	**map_reader(int fd, int *lanesize, int *n)
{
	char	c;
	char	*buf;
	char	**map;

	map = NULL;
	buf = (char *)ft_calloc(1, sizeof(char));
	if (read(fd, &c, 0) < 0)
		return (0);
	while (read(fd, &c, 1) > 0)
		buf = str_char_cat(buf, c);
	if (map_checker(buf, lanesize, n))
		map = map_to_tab(buf, *lanesize, *n);
	else
		error_map();
	free(buf);
	return (map);
}

void	arg_receiver(t_pos *pos, int *lanesize, int *n, char *argv)
{
	int		fd;
	int		fddircheck;

	*lanesize = 0;
	*n = 0;
	fd = open(argv, O_RDONLY);
	fddircheck = open(argv, O_DIRECTORY);
	if (fddircheck > 0)
		error_map();
	pos->map = map_reader(fd, lanesize, n);
	pos->lanesize = *lanesize;
	pos->n = *n + 1;
	close(fd);
}
