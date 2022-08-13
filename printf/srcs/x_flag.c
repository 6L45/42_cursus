/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:52:02 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:06 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_digits_x(unsigned int nb)
{
	int	digits;

	digits = 0;
	while (nb / 16)
	{
		digits++;
		nb /= 16;
	}
	digits++;
	return (digits);
}

void	ft_putx(unsigned int arg, int padding, int maj, t_flags *card)
{
	char	c;

	if (maj)
		c = 'A';
	else
		c = 'a';
	while (padding-- > 0)
		ft_putchar('0', card);
	if (arg / 16)
		ft_putx(arg / 16, padding, maj, card);
	if ((arg % 16) >= 10)
		ft_putchar((arg % 16) - 10 + c, card);
	else
		ft_putchar((arg % 16) + '0', card);
}

int	putlen_x(t_flags *card, unsigned int arg, int *padding, int *maj)
{
	int	len;

	*padding = 0;
	*maj = 0;
	len = ft_get_digits_x(arg);
	if (card->has_preci && card->preci == 0 && arg == 0)
		len = 0;
	if (len < card->preci)
		*padding = card->preci - len;
	else
		*padding = 0;
	if (card->f == 'X')
		*maj = 1;
	return (len + *padding);
}

void	ft_put_x(t_flags *card, va_list ap)
{
	int				len;
	unsigned int	arg;
	int				padding;
	int				maj;

	arg = (unsigned int)va_arg(ap, int);
	len = putlen_x(card, arg, &padding, &maj);
	if (card->minus || card->width < 0)
	{
		if (card->width < 0)
			card->width *= -1;
		if (!(card->has_preci && card->preci == 0 && arg == 0))
			ft_putx(arg, padding, maj, card);
		unsigned_width_putchar(card, len, 1);
		return ;
	}
	unsigned_width_putchar(card, len, 0);
	if (card->has_preci && card->preci == 0 && arg == 0)
		return ;
	ft_putx(arg, padding, maj, card);
}
