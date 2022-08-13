/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:11:39 by mberengu          #+#    #+#             */
/*   Updated: 2021/11/30 14:11:40 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*norminette_de_mon_coeur(char *tmp_seek_cmd, int findit)
{
	if (findit)
		return (tmp_seek_cmd);
	else
		return (NULL);
}

static char	*build_abs_adress_cmd(t_cmd *cmd, char **paths, int j)
{
	char	*tmp;
	char	*tmp_seek_cmd;

	if (paths[j][ft_strlen(paths[j]) - 1] != '/')
		tmp = ft_strjoin("/", cmd->commands[0]);
	else
		tmp = ft_strdup(cmd->commands[0]);
	tmp_seek_cmd = ft_strjoin(paths[j], tmp);
	free(tmp);
	return (tmp_seek_cmd);
}

static char	*seek_str_construct(t_cmd *cmd, char **paths)
{
	char	*tmp_seek_cmd;
	int		findit;
	int		j;

	j = 0;
	findit = 0;
	while (paths[j])
	{
		if (ft_strchr_str(paths[j], "bin") || ft_strchr_str(paths[j], "bin/"))
		{
			tmp_seek_cmd = build_abs_adress_cmd(cmd, paths, j);
			if (!access(tmp_seek_cmd, X_OK))
			{
				findit = 1;
				break ;
			}
			free(tmp_seek_cmd);
		}
		j++;
	}
	return (norminette_de_mon_coeur(tmp_seek_cmd, findit));
}

static void	bin_exec(t_cmd *cmd)
{
	char		*tmp_seek_cmd;
	struct stat	buf;

	tmp_seek_cmd = from_relative_path(cmd->commands[0]);
	exit_or_ret(SET, EXIT);
	execve(tmp_seek_cmd, cmd->commands, g_env);
	if (errno == 13)
	{
		if (!(lstat(tmp_seek_cmd, &buf)) && S_ISDIR(buf.st_mode))
		{
			free(tmp_seek_cmd);
			three_part_err("bash: ", cmd->commands[0], " :is a directory", 126);
		}
		free(tmp_seek_cmd);
		three_part_err("bash: ", cmd->commands[0], " :Permission denied", 126);
	}
	else if (errno == EFAULT)
		three_part_err("bash: ", cmd->commands[0],
			" :No such file or directory", 127);
	exit(EXIT_FAILURE);
}

void	child_process(t_cmd *cmd)
{
	char		*tmp_seek_cmd;
	char		*env;
	char		**paths;

	tmp_seek_cmd = NULL;
	if (cmd->commands[0] && !ft_strncmp(cmd->commands[0], "./", 2))
		bin_exec(cmd);
	env = get_env("PATH");
	paths = ft_split(env, ':');
	if (cmd->commands[0] && cmd->commands[0][0] == '/')
		tmp_seek_cmd = ft_strdup(cmd->commands[0]);
	else if (cmd->commands[0] && env)
		tmp_seek_cmd = seek_str_construct(cmd, paths);
	execve(tmp_seek_cmd, cmd->commands, g_env);
	execve_error_exits(cmd, tmp_seek_cmd);
	exit(EXIT_FAILURE);
}
