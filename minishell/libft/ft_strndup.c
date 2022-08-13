/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 06:27:20 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 06:27:23 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, int n)
{
	char	*dest;

	dest = (char *)ft_calloc((n + 1), sizeof(char));
	if (!dest)
	{
		dest = NULL;
		return (dest);
	}
	ft_strncpy(dest, s1, n);
	return (dest);
}
