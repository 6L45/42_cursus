/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:06:48 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:06:50 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*current_directory(int status)
{
	static char	cwd[400];
	char		*tmp;

	if (status == SET)
	{
		tmp = get_env("PWD");
		if (tmp)
			ft_strcpy(cwd, tmp);
		free(tmp);
	}
	else if (status == GET)
		return (ft_strdup(cwd));
	return (NULL);
}

int	sig_interrupted(int status)
{
	static int	boul = 0;

	if (status == SIG_INT)
		boul = 130;
	else if (status == SIG_QUIT)
		boul = 131;
	else if (status == RESET)
		boul = 0;
	return (boul);
}

int	exit_or_ret(int status, int value)
{
	static int	ret_status;

	if (status == SET)
		ret_status = value;
	return (ret_status);
}

char	*last_error_ret(int status, int lst_err)
{
	static int	last_err;

	if (status == GET)
		return (ft_itoa(last_err));
	last_err = lst_err;
	return (NULL);
}

char	*home_dir_loc(int status)
{
	static char	loc[400];
	char		*tmp;

	if (status == SET)
	{
		tmp = get_env("HOME");
		if (tmp)
			ft_strcpy(loc, tmp);
		free(tmp);
	}
	return (ft_strdup(loc));
}
