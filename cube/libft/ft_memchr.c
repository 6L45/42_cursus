/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:04:18 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 16:46:47 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char	*ptrs;
	size_t			i;

	ptrs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptrs[i] == (unsigned char)c)
			return ((void *)&ptrs[i]);
		i++;
	}
	return (0);
}
