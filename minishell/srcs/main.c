/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:32:45 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/24 12:32:47 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	extern char	**environ;

	write_g_env(environ);
	home_dir_loc(SET);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_receive_sig);
	prompt();
	return (0);
}
