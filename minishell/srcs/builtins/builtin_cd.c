/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:10:30 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:10:31 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_ret_handler(char *env_update)
{
	char	*swap;

	swap = ft_calloc(401, sizeof(char));
	getcwd(swap, 400);
	if (!swap[0])
	{
		free(swap);
		swap = current_directory(GET);
	}
	g_env_modif(ADD, "PWD", env_update, NULL);
	g_env_modif(ADD, "OLDPWD", swap, NULL);
	if (chdir(env_update))
	{
		write(2, "ERROR chdir\n", 12);
		free(swap);
		exit(EXIT_FAILURE);
	}
	current_directory(SET);
	free(swap);
}

static int	old_pwd_case(char **pwd, char **current, int output)
{
	int	j;

	j = find_env_var("OLDPWD");
	if (j >= 0)
	{
		(*pwd) = ft_strdup(&g_env[j][7]);
		ft_putstr_fd((*pwd), output);
		ft_putstr_fd("\n", output);
		cd_ret_handler(*pwd);
		last_error_ret(SET, 0);
	}
	else
	{
		write(2, "-bash: cd: OLDPWD not set\n", 26);
		last_error_ret(SET, 1);
	}
	free(*pwd);
	free(*current);
	return (0);
}

static int	env_situation(t_cmd *cmd, char **pwd, char ***address, int output)
{
	char	*current;

	current = ft_calloc(401, sizeof(char));
	getcwd(current, 400);
	if (!current[0])
	{
		free(current);
		current = current_directory(GET);
	}
	if (cmd->commands[0] && cmd->commands[1]
		&& !ft_strcmp(cmd->commands[1], "-"))
		return (old_pwd_case(pwd, &current, output));
	if (cmd->commands[1] && cmd->commands[1][0] == '/')
		(*pwd) = ft_strdup("/");
	else if (!cmd->commands[1])
	{
		if (!only_cd_case(pwd, &current))
			return (0);
	}
	else
		(*pwd) = ft_strdup(current);
	(*address) = ft_split(cmd->commands[1], '/');
	free(current);
	return (1);
}

static int	pwd_update(t_cmd *cmd, char **address, char **pwd)
{
	int	i;

	i = 0;
	while (address[i])
	{
		if (!ft_strcmp(address[i], ".") || !ft_strcmp(address[i], ".."))
			(*pwd) = point_dir(address[i], (*pwd));
		else if (!ft_strcmp(address[i], "~"))
			(*pwd) = home_dir(pwd);
		else
			(*pwd) = file_dir(&address, address[i], cmd->commands[1], pwd);
		if (!(*pwd))
			return (0);
		i++;
	}
	return (1);
}

void	cayday(t_cmd *cmd)
{
	int		output;
	char	*pwd;
	char	**address;

	pwd = NULL;
	output = STDOUT_FILENO;
	if (cmd->dest)
		output = cmd->dest;
	if (argc_from_cmd(cmd) > 2)
		too_many_args(CD);
	if (!(env_situation(cmd, &pwd, &address, output)))
		return ;
	if (cmd->commands[0] && cmd->commands[1])
	{
		if (!pwd_update(cmd, address, &pwd))
			return ;
	}
	ft_free_char_array(address);
	if (!access(pwd, F_OK))
		cd_ret_handler(pwd);
	if (pwd)
		free(pwd);
	last_error_ret(SET, 0);
}
