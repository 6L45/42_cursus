/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:09:54 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 13:09:57 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
