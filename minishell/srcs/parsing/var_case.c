/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:11 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:10:12 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insert_var_str(char *token_str, char *var, int i, int j)
{
	char	*base;
	char	*env_var;
	char	*tmp;
	char	*res;

	base = ft_strndup(token_str, i);
	if (token_str[i + 1] == '?')
	{
		j++;
		env_var = last_error_ret(GET, 0);
	}
	else
		env_var = get_env(var);
	if (!env_var)
	{
		free(env_var);
		env_var = ft_strdup("");
	}
	tmp = ft_strjoin(base, env_var);
	res = ft_strjoin(tmp, &token_str[j]);
	free(base);
	free(env_var);
	free(tmp);
	return (res);
}

void	var_case(t_tok *token, int pos)
{
	int		i;
	int		j;
	char	*var;
	char	*swap;

	i = -1;
	while (token->tokens[pos][++i])
	{
		if (token->tokens[pos][i] == '$'
			&& (token->tokens[pos][i + 1]
				&& (ft_isalpha(token->tokens[pos][i + 1])
					|| token->tokens[pos][i + 1] == '?')))
		{
			j = i + 1;
			while (token->tokens[pos][j] && ft_isalpha(token->tokens[pos][j]))
				j++;
			var = ft_strndup(&token->tokens[pos][i + 1], j - i - 1);
			swap = insert_var_str(token->tokens[pos], var, i, j);
			free(token->tokens[pos]);
			token->tokens[pos] = ft_strdup(swap);
			free(swap);
			free(var);
			i = 0;
		}
	}
}
