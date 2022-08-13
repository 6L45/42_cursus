/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:28:19 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/23 12:28:20 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_delimiter(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static void	libere(char **str, int i)
{
	while (--i > -1)
		free(str[i]);
	free(str);
}

static int	words_count(char const *s, char sep, int *x, int *y)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	*x = -1;
	*y = 0;
	while (s[i])
	{
		if (!is_delimiter(s[i], sep))
		{
			while (s[i] && !is_delimiter(s[i], sep))
				i++;
			count++;
		}
		while (s[i] && is_delimiter(s[i], sep))
			i++;
	}
	return (count);
}

static char	*ft_strdup_custom(char const *s, char c, int *j)
{
	int		i;
	int		k;
	char	*st;

	i = 0;
	k = 0;
	while (!is_delimiter(s[i], c) && s[i])
		i++;
	st = (char *)ft_calloc(i + 1, sizeof(char));
	if (!st)
		return (NULL);
	while (k < i)
	{
		st[k] = s[k];
		k++;
	}
	st[k] = '\0';
	while (is_delimiter(s[i], c) && s[i])
		i++;
	*j += i;
	return (st);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (0);
	count = words_count(s, c, &i, &j);
	str = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (is_delimiter(s[j], c) && s[j])
		j++;
	while (++i < count && s[j])
	{
		str[i] = ft_strdup_custom(&s[j], c, &j);
		if (!str[i])
		{
			libere(str, i);
			return (NULL);
		}
	}
	str[i] = 0;
	return (str);
}
