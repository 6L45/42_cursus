/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:19:29 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/24 16:19:31 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_pid(void)
{
	write(1, "PID : ", 6);
	ft_putnbr((long int)getpid());
	write(1, "\n", 1);
}

void	char_handler(int sign)
{
	static int	turn = 0;
	static char	character = 0;

	if (sign == SIGUSR1)
		character |= (1 << turn);
	turn += 1;
	if (turn == 8)
	{
		write(1, &character, 1);
		turn = 0;
		character = 0;
	}
}

void	sig_dealer(int sign, siginfo_t *info, void *context)
{
	(void)context;
	char_handler(sign);
	usleep(100);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_dealer;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	show_pid();
	while (1)
		pause();
	return (0);
}
