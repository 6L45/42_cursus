/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:08:53 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/22 13:08:55 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	args_inti(t_flags *card)
{
	card->f = 0;
	card->minus = 0;
	card->zero = 0;
	card->has_width = 0;
	card->width = 0;
	card->has_preci = 0;
	card->preci = 0;
}

void	arg_parsing(t_flags *card, va_list ap)
{
	if (card->f == 'c')
		ft_put_c(card, ap);
	if (card->f == 's')
		ft_put_s(card, ap);
	if (card->f == 'p')
		ft_put_p(card, ap);
	if (card->f == 'u')
		ft_put_u(card, ap);
	if (card->f == 'd' || card->f == 'i')
		ft_put_d(card, ap);
	if (card->f == 'x' || card->f == 'X')
		ft_put_x(card, ap);
}

int	flag_substitute(t_flags *card, char *str, va_list ap)
{
	int	i;

	i = 0;
	args_inti(card);
	flag_reader(card, str, ap);
	arg_parsing(card, ap);
	while (!ft_strchri("cspdiuxX", str[i])
		&& str[i + 1] && str[i] != '%')
		i++;
	return (i + 1);
}

void	str_print(char *str, t_flags *card, va_list ap)
{
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '%') %% x2
			{
				ft_putchar(*str, card);
				str++;
			}
			else
				str += flag_substitute(card, str, ap);
		}
		if (*str && *str != '%')
		{
			ft_putchar(*str, card);
			str++;
		}
	}
}

// l'ensemble de la fonction repose sur t_flag qui est "la carte d'identité" des flags lus
// cad : a chaque lecture de % la lecture du flag init les variables de la structure
// qui determineront les conditions pour le comportement de la fonction. 
// Type de flag, preci, largeur...etc
// voir .h
int	ft_printf(const char *format, ...)
{
	t_flags	card;
	va_list	ap;

	card.size = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	str_print((char *)format, &card, ap);
	va_end(ap);
	return (card.size);
}
