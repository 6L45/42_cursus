/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:52:00 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 14:52:02 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;
	size_t			i;

	ptrdst = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	i = 0;
	if (ptrdst == ptrsrc)
		return (dest);
	while (i < n)
	{
		ptrdst[i] = ptrsrc[i];
		if (ptrsrc[i] == (unsigned char)c)
			return (&ptrdst[i + (1 * sizeof(dest[i]))]);
		i++;
	}
	return (NULL);
}
