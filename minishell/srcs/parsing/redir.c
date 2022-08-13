/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:09:34 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:09:35 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_erase(char *cmdstr, int *i)
{
	int		j;

	j = 0;
	while (cmdstr[j] && (cmdstr[j] == '<'
			|| cmdstr[j] == '>' || cmdstr[j] == 32))
	{
		cmdstr[j] = 32;
		j++;
	}
	while (cmdstr[j] && cmdstr[j] > 32)
	{
		cmdstr[j] = 32;
		j++;
	}
	*i += j;
}

void	cmd_rewrite_redir(char *cmdstr)
{
	int		i;
	char	c;

	i = 0;
	while (cmdstr[i])
	{
		if (cmdstr[i] == '\'' || cmdstr[i] == '"')
		{
			c = cmdstr[i];
			i++;
			while (cmdstr[i] != c)
				i++;
		}
		if (cmdstr[i] == '<' || cmdstr[i] == '>')
			redir_erase(&cmdstr[i], &i);
		else
			i++;
	}
}

static int	output_cmd(char *token, t_cmd *cmd)
{
	int		i;
	char	*file;
	char	*tmptrim;

	i = 0;
	while ((token[i] && token[i] == '>')
		|| (token[i] > 0 && token[i] <= 32))
		i++;
	tmptrim = ft_strtrim(&token[i], " ");
	file = ft_strdup(tmptrim);
	free(tmptrim);
	if (cmd->dest)
		close (cmd->dest);
	if (token[1] == '>')
		cmd->dest = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else if (token[1] != '>')
		cmd->dest = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(file);
	return (1);
}

static int	input_cmd(char *token, t_cmd *cmd)
{
	int		i;
	char	*file;
	char	*tmptrim;

	i = 0;
	while ((token[i] && token[i] == '<')
		|| (token[i] > 0 && token[i] <= 32))
		i++;
	tmptrim = ft_strtrim(&token[i], " ");
	file = ft_strdup(tmptrim);
	free(tmptrim);
	if (cmd->src)
		close(cmd->src);
	cmd->src = open(file, O_RDONLY);
	free(file);
	if (cmd->src < 0)
		return (0);
	return (1);
}

int	redir_handler(char *token, t_cmd *cmd)
{
	if (token[0] == '>')
	{
		if (!output_cmd(token, cmd))
		{
			last_error_ret(SET, 2);
			return (0);
		}
	}
	else if (token[0] == '<')
	{
		if (token[1] && token[1] == '<')
		{
			if (!heredoc_ret_handler(token, cmd))
				return (0);
		}
		else if (!input_cmd(token, cmd))
			return (no_such_file_redir(token));
	}
	return (1);
}
