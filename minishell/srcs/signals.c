/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:06:01 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:06:03 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_receive_sig_after_fork(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		sig_interrupted(SIG_INT);
	}
	else if (signal == SIGQUIT)
	{
		printf("\n");
		sig_interrupted(SIG_QUIT);
	}
}

void	ft_receive_sig(int signal)
{
	if (signal == SIGINT)
	{
		last_error_ret(SET, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putstr("\e[2K");
		ft_putstr("minishell : ");
		ft_putstr("  \b\b\n");
		rl_redisplay();
	}
}
