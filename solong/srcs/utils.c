/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:55:33 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:55:34 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	plants_counter(t_pos *pos)
{
	int	i;
	int	j;
	int	plants;

	i = 0;
	j = 0;
	plants = 0;
	while (pos->map[i])
	{
		while (pos->map[i][j])
		{
			if (pos->map[i][j] == 'C')
				plants++;
			j++;
		}
		j = 0;
		i++;
	}
	return (plants);
}

void	where_is_charlie(t_pos *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (pos->map[x])
	{
		while (pos->map[x][y])
		{
			if (pos->map[x][y] == 'P')
			{
				pos->x = x;
				pos->y = y;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	display_prep(t_pos *pos)
{
	redraw(pos);
	pos->x *= 64;
	pos->y *= 64;
	pos->plants = 0;
}

int	lane_lenght(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
