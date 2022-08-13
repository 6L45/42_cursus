/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_min_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:58:16 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/03 16:58:18 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error_exits(t_cmd *cmd, char *tmp_seek_cmd)
{
	struct stat	buf;

	if (errno == 13)
	{
		if (!(lstat(tmp_seek_cmd, &buf)) && S_ISDIR(buf.st_mode))
			three_part_err("bash: ", cmd->commands[0], " :is a directory", 126);
		three_part_err("bash: ", cmd->commands[0], " :Permission denied", 126);
	}
	else if (errno == EFAULT)
		three_part_err(cmd->commands[0], ": ", "command not found", 127);
	else if (errno == 2)
		three_part_err(cmd->commands[0], ": ", "No such file or directory",
			127);
}

char	*env_var_res(char *command, int k, int *i)
{
	char	*var;
	char	*ret_env;

	var = ft_strndup(&command[1], k);
	ret_env = get_env(var);
	free(var);
	*i += k;
	return (ret_env);
}

char	*not_a_directory(DIR **dir, char **pwd, char *cmd, char ***address)
{
	three_part_err("bash: cd: ", cmd, ": Not a directory", -1);
	last_error_ret(SET, EXIT_FAILURE);
	free(*pwd);
	closedir(*dir);
	ft_free_char_array(*address);
	return (NULL);
}
