/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:58:54 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/29 16:58:56 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argc_from_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->commands[i])
		i++;
	return (i);
}

int	export_error_case(t_cmd *cmd, int i, int j)
{
	char	*var;

	while (cmd->commands[i][j] != '=')
		j++;
	var = ft_strndup(cmd->commands[i], j);
	last_error_ret(SET, EXIT_FAILURE);
	three_part_err("-bash: export: `", var,
		"': not a valid identifier", -1);
	free(var);
	return (-1);
}

int	home_not_set_err(char **pwd, char **current)
{
	write(2, "bash: cd: HOME not set\n", 23);
	free(*pwd);
	free(*current);
	return (0);
}

static void	print_it_by_putstrfd(char **sorted_env, int i, int output)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	if (contain_char(sorted_env[i], '='))
	{
		while (sorted_env[i][j] && sorted_env[i][j] != '=')
			j++;
		tmp = ft_strndup(sorted_env[i], j + 1);
		ft_putstr_fd("declare -x ", output);
		ft_putstr_fd(tmp, output);
		ft_putstr_fd("\"", output);
		ft_putstr_fd(&sorted_env[i][j + 1], output);
		ft_putstr_fd("\"\n", output);
		free(tmp);
	}
	else
	{
		ft_putstr_fd("declare -x ", output);
		ft_putstr_fd(sorted_env[i], output);
		ft_putstr_fd("\n", output);
	}
}

void	print_env_export_style(char **sorted_env, int output)
{
	int		i;

	i = 0;
	while (sorted_env[i])
	{
		print_it_by_putstrfd(sorted_env, i, output);
		i++;
	}
	exit (EXIT_SUCCESS);
}
