/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:52:50 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/27 11:52:51 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_reader_prepoint(t_flags *card, char *str, va_list ap)
{
	int	i;

	i = 0;
	while (str[i] != '.' && !ft_strchri("cspdiuxX", str[i]))
	{
		if (str[i] == '0')
			card->zero = 1;
		if (str[i] == '-')
			card->minus = 1;
		if (str[i] == '*')
		{
			card->has_width = 1;
			card->width = va_arg(ap, int);
		}
		if (ft_isdigit(str[i]) && str[i] != '0')
		{
			card->has_width = 1;
			card->width = ft_atoi(&str[i]);
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			i++;
	}
	return (i);
}

int	f_reader_postpoint(t_flags *card, char *str, va_list ap)
{
	int	i;

	i = 0;
	card->has_preci = 1;
	i++;
	while (!ft_strchri("cspdiuxX", str[i]))
	{
		if (str[i] == '*')
			card->preci = va_arg(ap, int);
		if (ft_isdigit(str[i]) && str[i] != '0')
		{
			card->preci = ft_atoi(&str[i]);
			while (ft_isdigit(str[i]))
				i++;
			i--;
		}
		i++;
	}
	return (i);
}

void	flag_reader(t_flags *card, char *str, va_list ap)
{
	str += f_reader_prepoint(card, str, ap);
	if (*str == '.')
		str += f_reader_postpoint(card, str, ap);
	// special cases 
	if (ft_strchri("cspdiuxX", *str))
	{
		card->f = *str;
		if ((card->minus && card->zero) || (card->width < 0)
			|| (card->has_preci && card->has_width && card->preci >= 0))
			card->zero = 0;
		if (card->preci < 0)
		{
			card->has_preci = 0;
			card->preci = 0;
		}
		return ;
	}
}
