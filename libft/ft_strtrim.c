/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:37:22 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/23 11:37:23 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_set(char c, char const *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	trim_left(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (is_set(s1[i], set) && s1[i])
		i++;
	return (i);
}

static int	trim_right(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (is_set(s1[i], set))
	{
		j++;
		i--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;
	int		limit;

	i = 0;
	j = -1;
	if (!s1)
		return (0);
	limit = ft_strlen(s1) - (trim_left(s1, set) + trim_right(s1, set));
	if (limit < 0)
		str = (char *)malloc(sizeof(char));
	else
		str = (char *)malloc(sizeof(char) * (limit + 1));
	if (!str)
		return (NULL);
	while (is_set(s1[i], set))
		i++;
	while (++j < limit)
		str[j] = s1[i + j];
	str[j] = '\0';
	return (str);
}
