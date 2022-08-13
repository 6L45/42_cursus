/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:10:36 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:31 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_digits_p(unsigned long int nb)
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

void	ft_putp(unsigned long int arg, int padding, t_flags *card)
{
	while (padding-- > 0)
		ft_putchar('0', card);
	if (arg / 16)
		ft_putp(arg / 16, padding, card);
	if ((arg % 16) >= 10)
		ft_putchar((arg % 16) - 10 + 'a', card);
	else
		ft_putchar((arg % 16) + '0', card);
}

void	unsigned_width_putchar(t_flags *card, int len, int i)
{
	int	fill;

	fill = ' ';
	if (card->zero && !card->has_preci && !i)
		fill = '0';
	while ((card->width - len) > 0)
	{
		ft_putchar(fill, card);
		card->width--;
	}
}

int	putlen_p(t_flags *card, unsigned long int arg, int *padding)
{
	int	len;

	*padding = 0;
	len = ft_get_digits_p(arg) + 2;
	if (card->has_preci && card->preci == 0 && arg == 0)
		len = 0;
	if (len < card->preci)
		*padding = card->preci - len;
	else
		*padding = 0;
	return (len + *padding);
}

void	ft_put_p(t_flags *card, va_list ap)
{
	int					len;
	unsigned long int	arg;
	int					padding;

	arg = (unsigned long int)va_arg(ap, long int);
	len = putlen_p(card, arg, &padding);
	if (card->minus || card->width < 0)
	{
		if (card->width < 0)
			card->width *= -1;
		if (!(card->has_preci && card->preci == 0 && arg == 0))
		{
			ft_putchar('0', card);
			ft_putchar('x', card);
			ft_putp(arg, padding, card);
		}
		unsigned_width_putchar(card, len, 1);
		return ;
	}
	unsigned_width_putchar(card, len, 0);
	if (card->has_preci && card->preci == 0 && arg == 0)
		return ;
	ft_putchar('0', card);
	ft_putchar('x', card);
	ft_putp(arg, padding, card);
}
