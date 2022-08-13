/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:01:20 by mberengu          #+#    #+#             */
/*   Updated: 2021/12/06 15:15:46 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_builtin(t_cmd *cmd)
{
	int	i;

	if (!ft_strcmp(cmd->commands[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->commands[0], "export"))
	{
		i = 0;
		while (cmd->commands[i])
			i++;
		if (i > 1)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(cmd->commands[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->commands[0], "exit"))
		return (1);
	return (0);
}

void	multipex(t_cmd *cmd, int i, int old_fd[2])
{
	int		fd[2];

	pipe(fd);
	signal(SIGINT, ft_receive_sig_after_fork);
	signal(SIGQUIT, ft_receive_sig_after_fork);
	if (!cmd[i].commands[0] && cmd[i + 1].index > 0)
		multipex(cmd, i + 1, fd);
	else if (!cmd[i].commands[0])
		return ;
	else
	{
		if (cmd[i].commands[0] && is_a_builtin(&cmd[i]))
			to_builtins(cmd, i, fd, old_fd);
		else
			to_fork(cmd, i, fd, old_fd);
	}
}
