/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:11:28 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:11:29 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_checker(t_cmd *cmd, int i, int j, int *addto)
{
	j = 0;
	if (cmd->commands[i][0] == '=')
	{
		write(2, "-bash: export: `=': not a valid identifier\n", 43);
		last_error_ret(SET, EXIT_FAILURE);
		return (-1);
	}
	while (cmd->commands[i][j] && cmd->commands[i][j] != '=')
	{
		if (cmd->commands[i][j] == '+' && cmd->commands[i][j + 1]
			&& cmd->commands[i][j + 1] == '=')
		{
			*addto = 1;
			break ;
		}
		else if ((!ft_isalpha(cmd->commands[i][j])
			&& !ft_isdigit(cmd->commands[i][j])
			&& !(cmd->commands[i][j] == '_'))
			|| (ft_isdigit(cmd->commands[i][0])))
			return (export_error_case(cmd, i, j));
		j++;
	}
	return (j);
}

static char	*concat_env_var(t_cmd *cmd, char *var, int i, int j)
{
	char	*base;
	char	*add;
	char	*value;

	base = get_env(var);
	if (base)
	{
		add = ft_strdup(&cmd->commands[i][j + 2]);
		value = ft_strjoin(base, add);
		free(base);
		free(add);
	}
	else
		value = ft_strdup(&cmd->commands[i][j + 2]);
	return (value);
}

static void	add_var(t_cmd *cmd, int i, int j, int addto)
{
	char	*var;
	char	*value;

	while (cmd->commands[++i])
	{
		j = var_checker(cmd, i, j, &addto);
		if (j < 0)
			return ;
		var = ft_strndup(cmd->commands[i], j);
		if (contain_char(cmd->commands[i], '=') && !addto)
			value = ft_strdup(&cmd->commands[i][j + 1]);
		else if (contain_char(cmd->commands[i], '=') && addto)
			value = concat_env_var(cmd, var, i, j);
		else
			value = NULL;
		g_env_modif(ADD, var, value, NULL);
		free(var);
		free(value);
	}
	last_error_ret(SET, EXIT_SUCCESS);
}

static void	sort_env(int output)
{
	int		i;
	int		j;
	int		num;
	char	*tmp;
	char	**sorted_env;

	i = 0;
	num = 0;
	sorted_env = copy_env();
	while (sorted_env[num])
		num++;
	while (++i < num)
	{
		j = i;
		while (j > 0 && ft_strcmp(sorted_env[j - 1], sorted_env[j]) > 0)
		{
			tmp = sorted_env[j - 1];
			sorted_env[j - 1] = sorted_env[j];
			sorted_env[j] = tmp;
			j--;
		}
	}
	i = 0;
	print_env_export_style(sorted_env, output);
	ft_free_char_array(sorted_env);
}

void	ex_port(t_cmd *cmd)
{
	int	i;
	int	j;
	int	output;
	int	addto;

	i = 0;
	j = 0;
	addto = 0;
	output = STDOUT_FILENO;
	if (argc_from_cmd(cmd) == 1)
		sort_env(output);
	else
		add_var(cmd, i, j, addto);
}
