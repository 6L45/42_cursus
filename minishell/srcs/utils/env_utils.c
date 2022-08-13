/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:25:19 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/24 21:25:21 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(void)
{
	int		i;
	char	**res;

	i = 0;
	while (g_env[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (g_env[i])
	{
		res[i] = ft_strdup(g_env[i]);
		i++;
	}
	return (res);
}

char	*get_env(char *var)
{
	int		i;
	int		len;
	int		res;
	char	*env_var;

	i = 0;
	res = 1;
	len = ft_strlen(var);
	env_var = NULL;
	while (g_env[i] && res)
	{
		res = ft_strncmp(g_env[i], var, len);
		i++;
	}
	if (!res)
		env_var = ft_strdup(&g_env[i - 1][len + 1]);
	return (env_var);
}

int	find_env_var(char *var)
{
	int		i;
	int		j;
	char	*g_env_var;

	i = 0;
	j = 0;
	while (g_env[i])
	{
		while (g_env[i][j] && g_env[i][j] != '=')
			j++;
		g_env_var = ft_strndup(g_env[i], j);
		j = 0;
		if (!ft_strcmp(g_env_var, var))
		{
			free(g_env_var);
			break ;
		}
		free(g_env_var);
		i++;
	}
	if (g_env[i])
		return (i);
	else
		return (-1);
}

char	**replacement_array_minus(int size, int j)
{
	int		i;
	int		k;
	char	**replacement;

	i = 0;
	k = 0;
	replacement = ft_calloc(size, sizeof(char *));
	while (g_env[i])
	{
		if (i == j)
			i++ ;
		if (g_env[i])
		{
			replacement[k] = ft_strdup(g_env[i]);
			i++;
		}
		k++;
	}
	return (replacement);
}

char	**replacement_array_plus(int size, char *var, char *value)
{
	int		i;
	char	*tmp;
	char	**replacement;

	i = 0;
	replacement = ft_calloc(size + 2, sizeof(char *));
	while (g_env[i])
	{
		replacement[i] = ft_strdup(g_env[i]);
		i++;
	}
	if (value)
	{
		tmp = ft_strjoin(var, "=");
		replacement[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
		replacement[i] = ft_strdup(var);
	replacement[i + 1] = 0;
	return (replacement);
}
