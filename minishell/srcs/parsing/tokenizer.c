/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:07:47 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:07:48 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenception(t_tok **token)
{
	int		i;
	int		j;
	t_tok	*tmp;

	i = 0;
	j = 0;
	tmp = *token;
	while (tmp)
	{
		tmp->tokens = get_tokens(tmp->cmd, tmp, i, j);
		tmp = tmp->next;
	}
}

static char	*trimed_str(char *str, int j)
{
	char	*tmp;
	char	*tmptrim;

	tmp = NULL;
	tmptrim = NULL;
	tmp = ft_strndup(str, j);
	tmptrim = ft_strtrim(tmp, " |");
	free(tmp);
	return (tmptrim);
}

static char	*str_till_pipe(char *str, int *i)
{
	int		j;
	char	c;

	j = 0;
	while (str[j] && ((str[j] > 0 && str[j] <= 32) || str[j] == '|'))
		j++;
	while (str[j] && str[j] != '|')
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			c = str[j];
			j++;
			while (str[j] != c)
				j++;
		}
		j++;
	}
	*i += j;
	return (trimed_str(str, j));
}

static void	token_init(t_tok **token, char *content)
{
	int		i;
	t_tok	*tok;

	i = 0;
	while (content[i])
	{
		tok = ft_calloc(1, sizeof(t_tok));
		tok->cmd = str_till_pipe(&content[i], &i);
		tok->tokens = NULL;
		tok->next = NULL;
		tok->type = NULL;
		fts_lstadd_back(token, tok);
	}
}

t_tok	*tokenizer(t_lex *lexer)
{
	t_tok	*token;

	token = NULL;
	token_init(&token, lexer->content);
	tokenception(&token);
	return (token);
}
