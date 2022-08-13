/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:36 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:10:37 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	n_special_case_check(char *cmdflag)
{
	int	i;

	i = 1;
	while (cmdflag[i])
	{
		if (cmdflag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	init_for_norme(t_cmd *cmd, int *i, short *n)
{
	int	output;

	*i = 1;
	*n = 0;
	output = STDOUT_FILENO;
	while (cmd->commands[*i]
		&& !ft_strncmp(cmd->commands[*i], "-n", 2)
		&& n_special_case_check(cmd->commands[*i]))
	{
		*i += 1;
		*n = 1;
	}
	return (output);
}

void	ekko(t_cmd *cmd)
{
	int		i;
	int		output;
	short	n;

	output = init_for_norme(cmd, &i, &n);
	while (cmd->commands[i])
	{
		ft_putstr_fd(cmd->commands[i], output);
		if (cmd->commands[i + 1])
			ft_putstr_fd(" ", output);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", output);
	exit(EXIT_SUCCESS);
}
