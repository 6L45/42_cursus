/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:02:11 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 11:02:42 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*s1;

	i = ft_strlen(s) - 1;
	s1 = (unsigned char *)s;
	if (!c)
		return ((char *)&s1[i + 1]);
	while (i >= 0)
	{
		if (s1[i] == (unsigned char)c)
			return ((char *)&s1[i]);
		i--;
	}
	return (NULL);
}
