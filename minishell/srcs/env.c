/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:05:31 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:05:32 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_all_env(char **new_env)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
	i = 0;
	while (new_env[i])
		i++;
	g_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (new_env[i])
	{
		g_env[i] = ft_strdup(new_env[i]);
		i++;
	}
	g_env[i] = 0;
}

static void	delete_on_env(char *var)
{
	int		i;
	int		j;
	char	**replacement;

	i = 0;
	j = find_env_var(var);
	if (j < 0)
		return ;
	while (g_env[i])
		i++;
	replacement = replacement_array_minus(i, j);
	replace_all_env(replacement);
	i = 0;
	while (replacement[i])
	{
		free(replacement[i]);
		i++;
	}
	free(replacement);
}

static void	replace_var_env(char *var, char *value, int j)
{
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	free(g_env[j]);
	g_env[j] = ft_strjoin(tmp, value);
	free(tmp);
}

static void	add_on_env(char *var, char *value)
{
	int		i;
	int		j;
	char	**replacement;

	i = 0;
	while (g_env[i])
		i++;
	j = find_env_var(var);
	if (j < 0)
	{
		replacement = replacement_array_plus(i, var, value);
		replace_all_env(replacement);
		i = 0;
		while (replacement[i])
		{
			free(replacement[i]);
			i++;
		}
		free(replacement);
	}
	else
	{
		if (value)
			replace_var_env(var, value, j);
	}
}

void	g_env_modif(int status, char *var, char *value, char **new_env)
{
	if (status == ADD)
		add_on_env(var, value);
	else if (status == DELETE)
		delete_on_env(var);
	else if (status == ALL)
		replace_all_env(new_env);
	else if (status == FREE)
		free_env();
}
