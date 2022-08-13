/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:04:03 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/22 17:04:05 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	j = 0;
	i = ft_strlen(dest);
	res = ft_strlen(src);
	if (size <= i)
		res += size;
	else
		res += i;
	while (src[j] && i + 1 < size)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (res);
}
