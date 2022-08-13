/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:31:54 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/23 13:31:56 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	size(int n)
{
	int	siz;

	siz = 0;
	if (n <= 0)
		siz++;
	while (n)
	{
		n /= 10;
		siz++;
	}
	return (siz);
}

char	*ft_itoa(int n)
{
	long int	space;
	long int	nbr;
	char		*toa;
	short		neg;

	neg = 0;
	nbr = n;
	space = (long int)size(nbr);
	if (nbr < 0)
	{
		nbr *= -1;
		neg = 1;
	}
	toa = (char *)malloc(sizeof(char) * space + 1);
	if (!toa)
		return (NULL);
	toa[space] = '\0';
	while (space--)
	{
		toa[space] = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	if (neg)
		toa[0] = '-';
	return (toa);
}
