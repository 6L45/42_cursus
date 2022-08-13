/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:29:03 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:29:04 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	player_set(int status)
{
	static int	set = 0;

	if (status == SET)
		set = 1;
	return (set);
}

int	authorized_char(char c)
{
	static int	plyer_set = 0;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player_set(SET);
		if (!plyer_set)
			plyer_set = 1;
		else
		{
			write(2, "Error : 2 players detected\n", 28);
			return (0);
		}
	}
	return (c == '0' || c == '1' || c == '\n' || c == 32
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	empty_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (!(*line >= 0 && *line <= 32))
			return (0);
		line++;
	}
	return (1);
}

void	err_print(t_fd_read *fdres, char *expected_value, int l)
{
	char	*tmp;

	tmp = ft_itoa(l);
	ft_putstr_fd("Error : line ", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(expected_value, 2);
	ft_putstr_fd(" expected\n", 2);
	free_and_quit(fdres, 1);
}
