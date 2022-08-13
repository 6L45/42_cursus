/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:51:52 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:51:53 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_digits(int nbr)
{
	int			digits;
	long int	nb;

	nb = nbr;
	digits = 0;
	if (nb < 0)
	{
		digits++;
		nb *= -1;
	}
	while (nb / 10)
	{
		digits++;
		nb /= 10;
	}
	digits++;
	return (digits);
}

void	ft_puti(long int arg, int padding, t_flags *card)
{
	if (arg < 0)
	{
		ft_putchar('-', card);
		arg *= -1;
	}
	while (padding-- > 0)
		ft_putchar('0', card);
	if (arg / 10)
		ft_puti(arg / 10, padding, card);
	ft_putchar((arg % 10) + '0', card);
}

void	width_putchar(t_flags *card, int len, int i, long int *arg)
{
	int	fill;

	fill = ' ';
	if (card->zero && !i)
		fill = '0';
	if (*arg < 0 && fill == '0' && !i)
	{
		ft_putchar('-', card);
		*arg = *arg * -1;
	}
	while ((card->width - len) > 0)
	{
		ft_putchar(fill, card);
		card->width--;
	}
}

int	putlen(t_flags *card, long int arg, int *padding)
{
	int	len;

	len = ft_get_digits(arg);
	if (card->has_preci && card->preci == 0 && arg == 0)
		len = 0;
	if (arg < 0)
	{
		if ((len - 1) < card->preci)
			*padding = card->preci - (len - 1);
		else
			*padding = 0;
	}
	else
	{
		if (len < card->preci)
			*padding = card->preci - len;
		else
			*padding = 0;
	}
	return (len + *padding);
}

void	ft_put_d(t_flags *card, va_list ap)
{
	long int	arg;
	int			len;
	int			padding;

	arg = va_arg(ap, int);
	len = putlen(card, arg, &padding);
	if (card->minus || card->width < 0)
	{
		if (card->width < 0)
			card->width *= -1;
		if (!(card->has_preci && card->preci == 0 && arg == 0))
			ft_puti(arg, padding, card);
		width_putchar(card, len, 1, &arg);
		return ;
	}
	if (card->has_preci && card->preci == 0 && arg == 0)
	{
		width_putchar(card, len, 1, &arg);
		return ;
	}
	width_putchar(card, len, 0, &arg);
	ft_puti(arg, padding, card);
	return ;
}
