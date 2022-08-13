/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:25:31 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/24 21:25:33 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*negative_return_res(char *command, int *i)
{
	char	*res;

	if ((*i == 0 && command[*i + 2] > 0 && command[*i + 2] <= 32)
		|| (*i > 1 && (command[*i -1] > 0 && command[*i - 1] <= 32)
			&& ((command[*i + 2] > 0 && command[*i + 2] <= 32)
				|| !command[*i + 2])))
	{
		*i += 2;
		return (ft_strdup(""));
	}
	*i += 2;
	res = ft_calloc(2, sizeof(char));
	res[0] = -1;
	return (res);
}

int	pass_quotes(char *str)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	if (!str[i])
		return (-1);
	while (str[i] != c)
	{
		if (!str[i])
			return (-1);
		i++;
	}
	if (str[i])
		i++;
	return (i);
}

int	heredoc_ret_handler(char *token, t_cmd *cmd)
{
	int	res;

	res = heredoc_handler(token, cmd);
	if (!res)
	{
		last_error_ret(SET, sig_interrupted(GET));
		sig_interrupted(RESET);
		return (0);
	}
	last_error_ret(SET, 0);
	return (1);
}

int	enum_type_return(char *str)
{
	char	c;
	char	c_pp;

	c = str[0];
	c_pp = 0;
	if (str[0] && str[1])
		c_pp = str[1];
	if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (D_QUOTE);
	else if (c == '>')
		return (REDIR_R);
	else if (c == '$')
		return (VAR);
	else if (c == '<')
	{
		if (c_pp == '<')
			return (HEREDOC);
		return (REDIR_L);
	}
	return (NORM);
}	

char	char_spec(char actual_c)
{
	char	c;

	c = 0;
	if (actual_c == '>')
		c = '>';
	if (actual_c == '<')
		c = '<';
	return (c);
}
