/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:19:10 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/24 16:19:13 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	prog_end(int err)
{
	free(g_arg2);
	exit(err);
}

void	char_dealer(int pid)
{
	static int	pos = 0;
	static int	i = 0;

	if (g_arg2[pos])
	{
		if ((g_arg2[pos] >> i) & 1)
		{	
			if (kill(pid, SIGUSR1) == -1)
				prog_end(1);
		}
		else
		{	
			if (kill(pid, SIGUSR2) == -1)
				prog_end(1);
		}
		i++;
		if (i == 8)
		{
			pos += 1;
			i = 0;
		}
	}
	else
		prog_end(0);
}

void	sig_dealer(int sign, siginfo_t *info, void *context)
{
	(void)context;
	usleep(100);
	if (sign == SIGUSR2)
		char_dealer(info->si_pid);
}

int	ft_parsing(char *argv, int *pid)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isdigit((int)argv[i]))
		{
			write(1, "Error PID\n", 10);
			prog_end(1);
		}
		i++;
	}
	*pid = ft_atoi(argv);
	if (kill(*pid, 0) != 0)
	{
		write(1, "BAD PID\n", 8);
		prog_end(1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_dealer;
	sigaction(SIGUSR2, &sig, NULL);
	if (argc == 3)
	{
		g_arg2 = ft_strdup(argv[2]);
		if (ft_parsing(argv[1], &pid))
		{
			char_dealer(pid);
			while (1)
				pause();
		}
	}
	else
	{
		write(1, "need 2 arguments: (PID) (TEXT)\n", 31);
		return (1);
	}
	return (0);
}
