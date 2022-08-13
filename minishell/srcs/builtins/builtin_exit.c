/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:59 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:11:01 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_nb_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->commands[i])
		i++;
	return (i);
}

static int	arg_cheker(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && (arg[i] == '-' || arg[i] == '+'))
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	init_for_norme(t_cmd *cmd, int *output)
{
	int		res;
	char	*alpha_ret;

	*output = STDOUT_FILENO;
	if (cmd->dest)
		*output = cmd->dest;
	alpha_ret = last_error_ret(GET, 0);
	res = ft_atoi(alpha_ret);
	free(alpha_ret);
	return (res);
}

static void	im_out(t_cmd *cmd, int value_exit)
{
	if (ft_get_nb_cmd(cmd) > 2)
	{
		ft_free_cmd(cmd);
		too_many_args(EXIT);
		return ;
	}
	ft_free_cmd(cmd);
	ft_free_char_array(g_env);
	clear_history();
	exit(value_exit);
}

void	ft_exit(t_cmd *cmd)
{
	unsigned long long int	ret;
	int						output;
	int						value_exit;
	int						neg;

	neg = 0;
	value_exit = init_for_norme(cmd, &output);
	ft_putstr_fd("exit\n", 2);
	if (cmd->commands[1])
	{
		ret = ((ft_atolli(cmd->commands[1], &neg)));
		if (!arg_cheker(cmd->commands[1])
			|| (ret > 9223372036854775807 && !neg)
			|| (ret > 9223372036854775808U && neg))
			three_part_err("bash: exit: ", cmd->commands[1],
				": numeric argument required", 2);
		value_exit = ret % 256;
		if (neg)
			value_exit *= -1;
	}
	im_out(cmd, value_exit);
}
