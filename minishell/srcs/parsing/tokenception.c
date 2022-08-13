/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenception.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:08:01 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:08:03 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_str(char *command, char **ret, int *i, int *type)
{
	int		j;
	char	c;

	j = 0;
	while (command[j] && !(command[j] > 0 && command[j] <= 32)
		&& !(command[j] == '<' || command[j] == '>'))
	{
		if (command[j] == '\'' || command[j] == '"')
		{
			c = command[j];
			if (!(*type))
				*type = enum_type_return(&command[j]);
			j++;
			while (command[j] != c)
				(*ret) = str_char_cat((*ret), command[j++]);
			j++;
		}
		else
		{
			(*ret) = str_char_cat((*ret), command[j]);
			j++;
		}
	}
	*i += j;
}

static char	*redirect_type(char *str, int *i, int *type)
{
	int		j;
	char	*base;
	char	*tmp;
	char	*res;

	j = 0;
	tmp = NULL;
	while (str[j] == '<' || str[j] == '>')
		j++;
	while (str[j] > 0 && str[j] <= 32)
		j++;
	*i += j;
	base = ft_strndup(str, j);
	token_str(&str[j], &tmp, i, type);
	res = ft_strjoin(base, tmp);
	free(base);
	free(tmp);
	return (res);
}

void	command_from_var(char ***res, char *command, int *i, int *j)
{
	int		k;
	int		old_size;
	char	*ret_env;

	k = 1;
	old_size = mem_tracker(GET, 0, TOKENCEPTION_VAR);
	while (ft_isalpha(command[k])
		|| command[k] == '_' || ft_isdigit(command[k]))
		k++;
	ret_env = env_var_res(command, k, i);
	if (!ret_env)
	{
		*j = 0;
		return ;
	}
	norminette_a_la_folie(res, &ret_env, j);
}

static char	*str_token(t_tok *token, char *command, int *i, int j)
{
	char	*res;
	char	*ret;

	res = NULL;
	ret = NULL;
	if ((command[*i] == '\'' || command[*i] == '"')
		&& (command[*i] == command[*i + 1]))
		return (negative_return_res(command, i));
	else if (command[*i] && char_spec(command[*i]))
	{
		token->type[j] = enum_type_return(&command[*i]);
		res = redirect_type(&command[*i], i, &token->type[j]);
	}
	else if (command[*i])
	{
		token_str(&command[*i], &ret, i, &token->type[j]);
		if (!token->type[j])
			token->type[j] = NORM;
		res = ft_strdup(ret);
		free(ret);
	}
	return (res);
}

char	**get_tokens(char *command, t_tok *token, int i, int j)
{
	char	**res;

	norminette_un_peu(&res);
	while (command[i])
	{
		norminette_beaucoup(command, &i);
		res = ft_realloc(res, sizeof(char *) * (j + 2), TOKENCEPTION_VAR);
		token->type = ft_realloc(token->type, sizeof(int *) * (j + 2),
				TOK_TYPE);
		norminette_passionnement(j);
		if (command[i] == '$' && command[i + 1] && command[i + 1] != '?'
			&& j == 0)
		{
			token->type[j] = enum_type_return(&command[i]);
			command_from_var(&res, &command[i], &i, &j);
		}
		else
		{
			res[j] = str_token(token, command, &i, j);
			res[j + 1] = NULL;
			j++;
		}
	}
	return (res);
}
