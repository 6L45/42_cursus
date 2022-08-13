/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:58:22 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/29 16:58:23 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	spec_case_builtin(char *command, t_cmd *cmd)
{
	int	i;

	if (!ft_strcmp(command, "cd"))
		return (1);
	else if (!ft_strcmp(command, "export"))
	{
		i = 0;
		while (cmd->commands[i])
			i++;
		if (i > 1)
			return (1);
		return (0);
	}
	else if (!ft_strcmp(command, "unset"))
		return (1);
	else if (!ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

static int	builtins_verif(t_cmd *cmd)
{
	int	i;
	int	btin;

	i = 0;
	btin = 0;
	while (cmd[i].index && cmd[i].commands[0])
	{
		if (spec_case_builtin(cmd[i].commands[0], &cmd[i]))
			btin++;
		i++;
	}
	if (!btin)
		return (1);
	return (0);
}

static void	builtin_cmd(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->commands[0], "echo"))
		ekko(cmd);
	else if (!ft_strcmp(cmd->commands[0], "cd"))
	{
		exit_or_ret(SET, RET);
		cayday(cmd);
	}
	else if (!ft_strcmp(cmd->commands[0], "pwd"))
		pay_doubleyu_di();
	else if (!ft_strcmp(cmd->commands[0], "export"))
		ex_port(cmd);
	else if (!ft_strcmp(cmd->commands[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->commands[0], "env"))
		henv(cmd);
	else if (!ft_strcmp(cmd->commands[0], "exit"))
		ft_exit(cmd);
}

static int	nbr_of_commands(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].index > 0)
		i++;
	return (i);
}

void	to_builtins(t_cmd *cmd, int i, int fd[2], int old_fd[2])
{
	close(old_fd[0]);
	close(old_fd[1]);
	if (cmd[i].src)
		close(cmd[i].src);
	if (!cmd[i].dest && cmd[i + 1].index > 0)
		cmd[i].dest = fd[1];
	if ((builtins_verif(&cmd[i])
			|| (!builtins_verif(&cmd[i]) && nbr_of_commands(cmd) == 1)))
		builtin_cmd(&cmd[i]);
	if (cmd[i + 1].index > 0)
		multipex(cmd, i + 1, fd);
	else
	{
		close(fd[0]);
		close(fd[1]);
		if (cmd[i].dest)
			close(cmd[i].dest);
	}
}
