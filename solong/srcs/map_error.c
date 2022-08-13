/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:53:13 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:53:14 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_map(void)
{
	write(2, "error map\n", 10);
	exit(0);
}

int	first_column_checker(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (buf[i + 1] && buf[i + 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int	first_and_last_lane_checker(char *buf, int n)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (buf[i] != '\n')
	{
		if (buf[i] != '1')
			return (0);
		i++;
	}
	while (newline <= n)
	{
		if (buf[i] == '\n')
			newline++;
		i++;
	}
	while (buf[i])
	{
		if (buf[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	error_check(char *buf, int lanelen, int lastlanelen, int last)
{
	if (last)
	{
		if (lanelen + 1 != lastlanelen || *buf != '1')
			error_map();
	}
	else
	{
		if (lanelen != lastlanelen || *buf != '1')
			error_map();
	}
}

short	map_checker(char *buf, int *lastlanelen, int *n)
{
	int	i;
	int	lanelen;

	i = 0;
	lanelen = 0;
	*lastlanelen = lane_lenght(buf);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			*n += 1;
			error_check(&buf[i - 1], lanelen, *lastlanelen, 0);
			i++;
			lanelen = 0;
		}
		if (!buf[i + 1])
			error_check(&buf[i], lanelen, *lastlanelen, 1);
		if (buf[i])
			i++;
		lanelen++;
	}
	if (first_and_last_lane_checker(buf, *n) && first_column_checker(buf)
		&& elements_count(buf))
		return (1);
	return (0);
}
