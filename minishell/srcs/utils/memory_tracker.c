/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tracker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:06:38 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:06:40 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenception_type_realloc(int status, int value)
{
	static int	val;

	if (status == SET)
		val = value;
	if (status == GET)
		return (val);
	return (0);
}

static int	tokenception_realloc(int status, int value)
{
	static int	val;

	if (status == SET)
		val = value;
	if (status == GET)
		return (val);
	return (0);
}

static int	redirl_set_realloc(int status, int value)
{
	static int	val;

	if (status == SET)
		val = value;
	if (status == GET)
		return (val);
	return (0);
}

int	mem_tracker(int status, int value, char *loc)
{
	if (ft_strcmp(loc, TOKENCEPTION_VAR))
		return (tokenception_realloc(status, value));
	else if (ft_strcmp(loc, REDIR_L_SET))
		return (redirl_set_realloc(status, value));
	else if (ft_strcmp(loc, TOK_TYPE))
		return (tokenception_type_realloc(status, value));
	return (0);
}
