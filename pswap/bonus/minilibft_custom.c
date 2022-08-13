/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft_custom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:03 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/25 10:26:56 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

long int	ft_atoi_custom(const char *str, int *j)
{
	long int	nbr;
	short		neg;
	int			i;

	nbr = 0;
	neg = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += (int)(str[i] - '0');
		i++;
	}
	*j += i;
	nbr *= neg;
	return (nbr);
}
