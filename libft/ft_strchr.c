/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:54:24 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 10:54:25 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char *)s;
	while (s1[i])
	{
		if (s1[i] == (unsigned char)c)
			return ((char *)&s1[i]);
		i++;
	}
	if (!c && !s1[i])
		return ((char *)&s1[i]);
	return (0);
}
