/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:51:28 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:51:29 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mvt_top(t_pos *pos)
{
	int	x;
	int	y;

	x = pos->x;
	y = pos->y;
	pos->plants = plants_counter(pos);
	if (x - 1 > 0 && pos->map[x - 1][y] != '1')
	{
		if (pos->map[x - 1][y] == 'E' && !pos->plants)
		{
			pos->endgame = UP;
			return (1);
		}
		else if (pos->map[x - 1][y] != 'E')
		{
			pos->map[x][y] = '0';
			pos->map[x - 1][y] = 'P';
			return (1);
		}
	}
	return (0);
}

int	mvt_right(t_pos *pos)
{
	int	x;
	int	y;

	x = pos->x;
	y = pos->y;
	pos->plants = plants_counter(pos);
	if (y + 1 > 0 && pos->map[x][y + 1] != '1')
	{
		if (pos->map[x][y + 1] == 'E' && !pos->plants)
		{
			pos->endgame = RIGHT;
			return (1);
		}
		else if (pos->map[x][y + 1] != 'E')
		{
			pos->map[x][y] = '0';
			pos->map[x][y + 1] = 'P';
			return (1);
		}
	}
	return (0);
}

int	mvt_left(t_pos *pos)
{
	int	x;
	int	y;

	x = pos->x;
	y = pos->y;
	pos->plants = plants_counter(pos);
	if (y - 1 > 0 && pos->map[x][y - 1] != '1')
	{
		if (pos->map[x][y - 1] == 'E' && !pos->plants)
		{
			pos->endgame = LEFT;
			return (1);
		}
		else if (pos->map[x][y - 1] != 'E')
		{
			pos->map[x][y] = '0';
			pos->map[x][y - 1] = 'P';
			return (1);
		}
	}
	return (0);
}

int	mvt_down(t_pos *pos)
{
	int	x;
	int	y;

	x = pos->x;
	y = pos->y;
	pos->plants = plants_counter(pos);
	if (x + 1 > 0 && pos->map[x + 1][y] != '1')
	{
		if (pos->map[x + 1][y] == 'E' && !pos->plants)
		{
			pos->endgame = DOWN;
			return (1);
		}
		else if (pos->map[x + 1][y] != 'E')
		{
			pos->map[x][y] = '0';
			pos->map[x + 1][y] = 'P';
			return (1);
		}
	}
	return (0);
}

int	map_adjustment(t_pos *pos, int mvt, int *nbr)
{
	int	x;
	int	y;

	x = pos->x;
	y = pos->y;
	if (mvt == UP)
		if (mvt_top(pos))
			return (*nbr += 1);
	if (mvt == RIGHT)
		if (mvt_right(pos))
			return (*nbr += 1);
	if (mvt == LEFT)
		if (mvt_left(pos))
			return (*nbr += 1);
	if (mvt == DOWN)
		if (mvt_down(pos))
			return (*nbr += 1);
	return (0);
}
