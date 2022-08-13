/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:27 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/01 12:08:28 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src || !dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char **s1, char **s2)
{
	int		i;
	int		j;
	char	*str;
	char	*sup;

	if (!*s2)
		return (0);
	i = ft_strlen(*s1);
	j = -1;
	sup = *s2;
	str = (char *)ft_calloc((ft_strlen(*s1) + 1 + ft_strlen(*s2) + 1),
			sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, *s1);
	while (sup[++j])
		str[i + j] = sup[j];
	str[i + j] = '\0';
	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	return (str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*pts;
	size_t	i;

	pts = (char *)s;
	i = 0;
	while (i < n)
	{
		pts[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	new = malloc(nmemb * size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, (nmemb * size));
	return (new);
}

void	ft_strchr(char **line, int c, char **backup)
{
	int				i;
	int				j;
	int				k;
	unsigned char	*s1;
	char			*str;

	i = 0;
	k = -1;
	j = ft_strlen(*backup);
	s1 = (unsigned char *)*line;
	while (s1[i])
	{
		if (s1[i] == (unsigned char)c)
			break ;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + j + 2));
	ft_strcpy(str, *backup);
	while (++k < i)
		str[j + k] = s1[k];
	str[j + k] = '\0';
	ft_strcpy(*backup, (char *)&s1[i + 1]);
	free(*line);
	*line = str;
}
