/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:58:30 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/29 16:58:32 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printing_builtins(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->commands[0], "echo"))
		ekko(cmd);
	else if (!ft_strcmp(cmd->commands[0], "pwd"))
		pay_doubleyu_di();
	else if (!ft_strcmp(cmd->commands[0], "export"))
		ex_port(cmd);
	else if (!ft_strcmp(cmd->commands[0], "env"))
		henv(cmd);
}

static void	main_process(t_cmd *cmd, int i, int fd[2], int old_fd[2])
{
	int	status;

	if (cmd[i].src)
		close(cmd[i].src);
	if (cmd[i].dest)
		close(cmd[i].dest);
	close(old_fd[0]);
	close(old_fd[1]);
	if (cmd[i + 1].index > 0)
		multipex(cmd, i + 1, fd);
	else
	{
		while (waitpid(-1, &status, 0) > 0)
			last_error_ret(SET, WEXITSTATUS(status));
		close(fd[0]);
		signal(SIGINT, ft_receive_sig);
		signal(SIGQUIT, SIG_IGN);
	}
}

static void	fd_buisness(t_cmd *cmd, int fd[2], int old_fd[2])
{
	if (cmd[1].index != 0 && !cmd->dest)
		dup2(fd[1], STDOUT_FILENO);
	if (cmd->index != 1 && !cmd->src)
		dup2(old_fd[0], STDIN_FILENO);
	if (cmd->dest)
	{
		dup2(cmd->dest, STDOUT_FILENO);
		close(cmd->dest);
	}
	if (cmd->src)
	{
		dup2(cmd->src, STDIN_FILENO);
		close(cmd->src);
	}
}

void	to_fork(t_cmd *cmd, int i, int fd[2], int old_fd[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		write(2, "bash: fork: Ressource temporarily unavailable\n", 50);
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fd_buisness(&cmd[i], fd, old_fd);
		close(old_fd[0]);
		close(old_fd[1]);
		close(fd[0]);
		close(fd[1]);
		printing_builtins(&cmd[i]);
		child_process(&cmd[i]);
	}
	main_process(cmd, i, fd, old_fd);
}
