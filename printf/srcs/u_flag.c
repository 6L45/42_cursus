/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:52:11 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:12 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_digits_u(int nbr)
{
	int				digits;
	unsigned int	nb;

	nb = nbr;
	digits = 0;
	while (nb / 10)
	{
		digits++;
		nb /= 10;
	}
	digits++;
	return (digits);
}

void	ft_putu(unsigned int arg, int padding, t_flags *card)
{
	while (padding-- > 0)
		ft_putchar('0', card);
	if (arg / 10)
		ft_putu(arg / 10, padding, card);
	ft_putchar((arg % 10) + '0', card);
}

int	putlen_u(t_flags *card, unsigned int arg, int *padding)
{
	int	len;

	*padding = 0;
	len = ft_get_digits_u(arg);
	if (card->has_preci && card->preci == 0 && arg == 0)
		len = 0;
	else
	{
		if (len < card->preci)
			*padding = card->preci - len;
		else
			*padding = 0;
	}
	return (len + *padding);
}

void	ft_put_u(t_flags *card, va_list ap)
{
	unsigned int	arg;
	int				len;
	int				padding;

	arg = (unsigned int)va_arg(ap, int);
	len = putlen_u(card, arg, &padding);
	if (card->minus || card->width < 0)
	{
		if (card->width < 0)
			card->width *= -1;
		if (!(card->has_preci && card->preci == 0 && arg == 0))
			ft_putu(arg, padding, card);
		unsigned_width_putchar(card, len, 1);
		return ;
	}
	unsigned_width_putchar(card, len, 0);
	if (card->has_preci && card->preci == 0 && arg == 0)
		return ;
	ft_putu(arg, padding, card);
	return ;
}
