/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:09:45 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:09:46 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_dir(char **pwd)
{
	free(*pwd);
	return (home_dir_loc(GET));
}

char	*point_dir(char *commands, char *pwd)
{
	int		pwd_len;
	char	*tmp;

	pwd_len = ft_strlen(pwd);
	if (!ft_strcmp(commands, "."))
		;
	else if (!ft_strcmp(commands, ".."))
	{
		while (pwd_len > 0 && pwd[pwd_len] != '/')
			pwd_len--;
		if (pwd_len == 0)
		{
			free(pwd);
			pwd = ft_strdup("/");
		}
		else
		{
			tmp = ft_strndup(pwd, pwd_len);
			free(pwd);
			pwd = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (pwd);
}

char	*file_dir(char ***address, char *commands, char *cmd, char **pwd)
{
	DIR				*dir;
	struct dirent	*entity;
	int				match;

	match = 1;
	dir = opendir(*pwd);
	entity = readdir(dir);
	while (entity != NULL)
	{
		match = ft_strcmp(commands, entity->d_name);
		if (!match && entity->d_type == 4)
			break ;
		else if (!match && entity->d_type != 4)
			return (not_a_directory(&dir, pwd, cmd, address));
		entity = readdir(dir);
	}
	if (pwd_res(pwd, commands, match))
		return (no_such_file_path_handler(cmd, &dir, pwd, address));
	closedir(dir);
	return (*pwd);
}

static char	*access_check(char ***address, char *commands, char *pwd)
{
	char	*base;
	char	*res;

	base = ft_strdup(pwd);
	base = str_char_cat(base, '/');
	res = ft_strjoin(base, commands);
	ft_free_char_array(*address);
	if (access(res, F_OK) < 0)
	{
		free(res);
		res = NULL;
	}
	free(base);
	free(pwd);
	return (res);
}

char	*from_relative_path(char *cmd)
{
	int		i;
	char	*pwd;
	char	**address;

	i = 0;
	pwd = ft_calloc(401, sizeof(char));
	getcwd(pwd, 400);
	address = ft_split(cmd, '/');
	while (address[i])
	{
		if (!ft_strcmp(address[i], ".") || !ft_strcmp(address[i], ".."))
			pwd = point_dir(address[i], pwd);
		else if (!ft_strcmp(address[i], "~"))
			pwd = home_dir(&pwd);
		else if (address[i] && !address[i + 1])
			return (access_check(&address, address[i], pwd));
		else
			pwd = file_dir(&address, address[i], cmd, &pwd);
		i++;
	}
	ft_free_char_array(address);
	return (pwd);
}
