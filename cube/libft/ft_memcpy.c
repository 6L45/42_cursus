/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:38:52 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 14:38:53 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dest);
}
