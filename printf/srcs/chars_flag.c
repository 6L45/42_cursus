/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:52:22 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:23 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_c(t_flags *card, va_list ap)
{
	int	ch;

	ch = va_arg(ap, int);
	if (card->width)
	{
		if (card->minus || card->width < 0)
		{
			if (card->width < 0)
				card->width *= -1;
			ft_putchar(ch, card);
			while ((card->width-- - 1) > 0)
				ft_putchar(' ', card);
		}
		else
		{
			while ((card->width-- - 1) > 0)
				ft_putchar(' ', card);
			ft_putchar(ch, card);
		}
	}
	else
		ft_putchar(ch, card);
}

void	ft_putstr_card(char *str, t_flags *card)
{
	int	i;

	if (card->has_preci)
		i = card->preci;
	else
		i = ft_strlen(str);
	while (*str && i)
	{
		ft_putchar(*str, card);
		str++;
		i--;
	}
}

void	ft_putstrl(char *str, int len, t_flags *card)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		ft_putchar(str[i], card);
		i++;
	}
}

int	putlen_chars(t_flags *card, char *s)
{
	int	putlen;
	int	len;

	len = ft_strlen(s);
	if (!card->has_preci && !card->has_width)
	{
		ft_putstrl(s, len, card);
		return (-1);
	}
	if (card->has_preci && len > card->preci)
		putlen = card->preci;
	else
		putlen = len;
	return (putlen);
}

void	ft_put_s(t_flags *card, va_list ap)
{
	char	*s;
	int		putlen;

	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	putlen = putlen_chars(card, s);
	if (putlen < 0)
		return ;
	if (card->minus || card->width < 0)
	{
		if (card->width < 0)
			card->width *= -1;
		ft_putstrl(s, putlen, card);
		while ((card->width-- - putlen) > 0)
			ft_putchar(' ', card);
	}
	else
	{
		while ((card->width-- - putlen) > 0)
			ft_putchar(' ', card);
		ft_putstrl(s, putlen, card);
	}
}
