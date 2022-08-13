/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:04:50 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 16:04:51 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;
	size_t			i;

	if (s1 == s2 || n == 0)
		return (0);
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1 && ptrs1[i] == ptrs2[i])
		i++;
	return (ptrs1[i] - ptrs2[i]);
}
