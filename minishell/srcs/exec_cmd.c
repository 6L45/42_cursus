/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 06:10:22 by mberengu          #+#    #+#             */
/*   Updated: 2021/12/06 15:02:26 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_tok **token, t_cmd **cmd, char *user_entry)
{
	int	fd[2];
	int	pipe_ret;

	pipe_ret = pipe(fd);
	if (pipe_ret < 0 || !user_entry)
	{
		perror(NULL);
		return ;
	}
	if (tokens_to_cmd((*cmd), token))
		multipex((*cmd), 0, fd);
}

static int	nbr_of_pipe(char *str_argv)
{
	int		res;
	char	c;

	res = 0;
	while (*str_argv)
	{
		str_argv++;
		if (*str_argv == '\'' || *str_argv == '"')
		{
			c = *str_argv;
			str_argv++;
			while (*str_argv && *str_argv != c)
				str_argv++;
		}
		if (*str_argv == '|')
			res++;
	}
	return (res);
}

void	cmds_buisness(char *user_entry, t_tok **token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(nbr_of_pipe(user_entry) + 2, sizeof(t_cmd));
	if (!cmd)
	{
		perror(NULL);
		return ;
	}
	exec_cmd(token, &cmd, user_entry);
	free_token(token);
	ft_free_cmd((cmd));
}
