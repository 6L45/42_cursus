/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:07:02 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:07:03 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

void	ft_free_char_array(char **char_array)
{
	int		i;

	if (!char_array)
		return ;
	i = 0;
	while (char_array[i])
		free(char_array[i++]);
	free(char_array);
}

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd[0].index)
		return ;
	i = 0;
	while (cmd[i].index > 0)
	{
		ft_free_char_array(cmd[i].commands);
		if (cmd[i].src)
			close(cmd[i].src);
		if (cmd[i].dest)
			close(cmd[i].dest);
		i++;
	}
	free(cmd);
}

void	free_token(t_tok **token)
{
	int		i;
	t_tok	*tok;

	i = 0;
	tok = *token;
	while (tok)
	{
		while (tok->tokens[i])
		{
			free(tok->tokens[i]);
			i++;
		}
		free(tok->cmd);
		free(tok->tokens);
		free(tok->type);
		i = 0;
		tok = (*token)->next;
		free(*token);
		(*token) = tok;
	}
}
