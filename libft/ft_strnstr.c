/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:28:48 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 11:28:50 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[j])
		{
			while ((s1[i + j] == s2[j] && (i + j < n)))
			{
				if (!s2[j + 1])
					return ((char *)&s1[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
