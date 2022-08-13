/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:07:20 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:07:22 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_return(int from)
{
	if (from == 24)
		ft_putstr_fd("Error: OR '||' detected\n", 2);
	else if (from == 40)
		ft_putstr_fd("Error: user entry finishing with a pipe\n", 2);
	else if (from == 45)
		ft_putstr_fd("-bash: syntax error near unexpected token `|'\n", 2);
	else if (from == 21)
		ft_putstr_fd("Error: quote missing\n", 2);
	last_error_ret(SET, 258);
	return (0);
}

void	too_many_args(int from)
{
	if (from == CD)
		write(2, "-bash: cd: too many arguments\n", 30);
	else
		write(2, "-bash: exit: too many arguments\n", 32);
	last_error_ret(SET, 1);
}

int	no_such_file_redir(char *token)
{
	ft_putstr_fd("bash : ", 2);
	while (*token && (*token == '<' || (*token > 0 && *token <= 32)))
		token++;
	ft_putstr_fd(token, 2);
	write(2, ": No such file or directory\n", 28);
	last_error_ret(SET, 1);
	return (0);
}

char	*no_such_file_path_handler(char *cmd, DIR **dir,
	char **pwd, char ***address)
{
	write(2, "-bash: ", 7);
	ft_putstr_fd(cmd, 2);
	write(2, ": No such file or directory\n", 28);
	closedir(*dir);
	free(*pwd);
	ft_free_char_array(*address);
	if (exit_or_ret(GET, 0) == EXIT)
		exit(EXIT_FAILURE);
	last_error_ret(SET, EXIT_FAILURE);
	return (NULL);
}

void	three_part_err(char *strstart, char *cmd, char *strend, int out)
{
	ft_putstr_fd(strstart, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(strend, 2);
	write(2, "\n", 1);
	if (out > 0)
		exit(out);
}
