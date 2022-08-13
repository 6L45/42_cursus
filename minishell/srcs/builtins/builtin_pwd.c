/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:11:42 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:11:44 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pay_doubleyu_di(void)
{
	int		output;
	char	*current;

	output = STDOUT_FILENO;
	current = ft_calloc(401, sizeof(char));
	getcwd(current, 400);
	if (!current[0])
	{
		free(current);
		current = current_directory(GET);
	}
	ft_putstr_fd(current, output);
	ft_putstr_fd("\n", output);
	free(current);
	exit(EXIT_SUCCESS);
}
