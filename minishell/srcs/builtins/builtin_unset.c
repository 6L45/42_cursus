/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:11:51 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:11:52 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->commands[0] && !cmd->commands[1])
		exit(127);
	while (cmd->commands[i])
	{
		g_env_modif(DELETE, cmd->commands[i], NULL, NULL);
		i++;
	}
	last_error_ret(SET, EXIT_SUCCESS);
}
