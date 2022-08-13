/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:00 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:10:01 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error_check(char *content, char c_entry, int *i)
{
	while (content[*i] && content[*i] == c_entry)
		*i += 1;
	while (content[*i] && (content[*i] > 0 && content[*i] <= 32))
		*i += 1;
	if (!content[*i] || content[*i] == '('
		|| content[*i] == ')' || content[*i] == '|'
		|| content[*i] == '<' || content[*i] == '>')
	{
		if ((!content[*i]) || (content[*i] > 0 && content[*i] <= 32))
			ft_putstr_fd("bash: syntax error near \
unexpected token `newline'\n", 2);
		else
			three_part_err("bash: syntax error near \
unexpected token `", &content[*i], "'", -1);
		last_error_ret(SET, 258);
		return (0);
	}
	return (1);
}

static int	pipe_redir_check(char *content, int *i)
{
	if (content[*i] == '|')
	{
		*i += 1;
		if (!content[*i])
			return (syntax_error_return(40));
		else if (content[*i] == '|')
			return (syntax_error_return(24));
		while (content[*i] > 0 && content[*i] <= 32)
		{
			*i += 1;
			if (!content[*i])
				return (syntax_error_return(40));
			else if (content[*i] == '|')
				return (syntax_error_return(45));
		}
	}
	else if (content[*i] == '<' || content[*i] == '>')
	{
		if (!redir_error_check(content, content[*i], i))
			return (0);
	}
	return (1);
}

static int	basic_syntax_checker(char *content)
{
	int		i;
	int		quote_ret;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '"')
		{
			quote_ret = pass_quotes(&content[i]);
			if (quote_ret < 0)
				return (syntax_error_return(21));
			i += quote_ret;
		}
		else if (content[i] == '|' || content[i] == '<' || content[i] == '>')
		{
			if (!pipe_redir_check(content, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

static int	entry_format(char *content)
{
	int	i;

	i = 0;
	while (content[i] && (content[i] > 0 && content[i] <= 32))
		i++;
	if (content[0] == '|' || content[i] == '|')
	{
		ft_putstr_fd("-bash: syntax error near unexpected token `|'\n", 2);
		last_error_ret(SET, 2);
		return (0);
	}
	if (!basic_syntax_checker(content))
		return (0);
	return (1);
}

t_tok	*dura_lex_sed_lex(char **content)
{
	t_lex	*lexer;
	t_tok	*token;

	token = NULL;
	lexer = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lexer->result = (char **)ft_calloc(1, sizeof(char *));
	if (entry_format(*content))
	{
		lexer->content = ft_strdup(*content);
		token = tokenizer(lexer);
		free(lexer->content);
	}
	free(lexer->result);
	free(lexer);
	return (token);
}
