/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 09:22:16 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/23 09:22:18 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	size_t			min_len;
	unsigned char	*str;

	j = -1;
	if (!s)
		return (0);
	min_len = ft_strlen(&s[start]);
	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (min_len < len)
		len = min_len;
	str = (unsigned char *)malloc((sizeof(unsigned char) * (len + 1)));
	if (!str)
		return (NULL);
	while (s[start + (++j)] && len--)
		str[j] = s[start + j];
	str[j] = '\0';
	return ((char *) str);
}
