/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:08:13 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:08:15 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**cmd_array_create(t_tok *token, char **res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->tokens[j])
	{
		while (token->tokens[j]
			&& (token->tokens[j][0] == '>'
			|| token->tokens[j][0] == '<' || token->tokens[j][0] < 0))
			j++;
		if (token->tokens[j])
			res[i] = ft_strdup(token->tokens[j]);
		else
			res[i] = NULL;
		i++;
		if (token->tokens[j])
			j++;
	}
	return (res);
}

static char	**cmds_strdup_array(t_tok *token)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = NULL;
	while (token->tokens[i])
	{
		if (token->tokens[i][0] == '>' || token->tokens[i][0] == '<')
			j++;
		i++;
	}
	res = ft_calloc((i - j) + 1, sizeof(char *));
	return (cmd_array_create(token, res));
}

static int	cmd_array_init(t_cmd *cmd, t_tok *token)
{
	int		j;
	t_tok	*tmp;

	j = 0;
	tmp = token;
	while (tmp->tokens[j])
	{
		if (tmp->tokens[j][0] == '<' || tmp->tokens[j][0] == '>')
		{
			if (!redir_handler(tmp->tokens[j], cmd))
				return (0);
			cmd_rewrite_redir(tmp->cmd);
		}
		else if (contain_char(tmp->tokens[j], '$') && tmp->type[j] != QUOTE)
			var_case(tmp, j);
		j++;
	}
	return (1);
}

int	tokens_to_cmd(t_cmd *cmd, t_tok **token)
{
	int		i;
	t_tok	*tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		cmd[i].src = 0;
		cmd[i].dest = 0;
		cmd[i].index = i + 1;
		if (!cmd_array_init(&cmd[i], tmp))
			return (0);
		cmd[i].commands = cmds_strdup_array(tmp);
		tmp = tmp->next;
		i++;
	}
	return (1);
}
