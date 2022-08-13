/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:33:51 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 15:33:52 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;
	size_t			i;

	ptrdst = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (ptrdst > ptrsrc)
		while (len-- > 0)
			ptrdst[len] = ptrsrc[len];
	else
	{
		while (i < len)
		{
			ptrdst[i] = ptrsrc[i];
			i++;
		}
	}
	return (dest);
}
