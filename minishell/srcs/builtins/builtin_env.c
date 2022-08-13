/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:52 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:10:53 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_environ(void)
{
	int		i;
	int		output;
	char	*tmp;

	i = 0;
	output = STDOUT_FILENO;
	while (g_env[i])
	{
		if (contain_char(g_env[i], '='))
		{
			tmp = ft_strjoin(g_env[i], "\n");
			ft_putstr_fd(tmp, output);
			free(tmp);
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	henv(t_cmd *cmd)
{
	if (argc_from_cmd(cmd) > 1)
	{
		three_part_err("env: ‘", cmd->commands[1],
			"’: No such file or directory", -1);
		exit(127);
		return ;
	}
	print_environ();
}
