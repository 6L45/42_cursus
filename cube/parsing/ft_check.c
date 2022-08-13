/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:06 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:07 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	first_carac_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j] && (fdres->map[i][j] > 0 && fdres->map[i][j] <= 32))
	{
		if (!authorized_char(fdres->map[i][j]))
			err_map(fdres);
		j++;
	}
	if (fdres->map[i][j] != '1')
		err_map(fdres);
}

void	last_carac_checker(t_fd_read *fdres, int i, int j)
{
	int	k;

	k = 0;
	while (j - k > 0 && (fdres->map[i][j - k] > 0
		&& fdres->map[i][j - k] <= 32))
	{
		if (!authorized_char(fdres->map[i][j - k]))
			err_map(fdres);
		k++;
	}
	if (fdres->map[i][j - k] != '1')
		err_map(fdres);
}

void	map_scanning(t_fd_read *fdres, int i, int j)
{
	if ((fdres->map[i][j] != '1' && fdres->map[i][j] != 32
		&& (fdres->map[i + 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1]
				&& fdres->map[i + 1][j + 1] == 32)
			|| fdres->map[i + 1][j - 1] == 32
			|| fdres->map[i - 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1]
				&& fdres->map[i - 1][j + 1] == 32)
			|| fdres->map[i - 1][j - 1] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1]
				&& fdres->map[i][j + 1] == 32)
			|| fdres->map[i][j - 1] == 32))
		|| !authorized_char(fdres->map[i][j]))
		err_map(fdres);
}

void	space_checker(t_fd_read *fdres, int i, int j)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	while (fdres->map[i][j + l] && (fdres->map[i][j + l] > 0
		&& fdres->map[i][j + l] <= 32))
	{
		if (!authorized_char(fdres->map[i][j + l]))
			err_map(fdres);
		l++;
	}
	while (j - k > 0 && fdres->map[i][j - k]
		&& (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32))
	{
		if (!authorized_char(fdres->map[i][j - k]))
			err_map(fdres);
		k++;
	}
	if ((fdres->map[i][j + l] != '1' && fdres->map[i][j + l])
		|| (fdres->map[i][j - k] != '1' && j - k != 0))
		err_map(fdres);
}

void	first_last_line_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j])
	{
		if (fdres->map[i][j] != 32 && fdres->map[i][j] != '1')
			err_map(fdres);
		j++;
	}
}
