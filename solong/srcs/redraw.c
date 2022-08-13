/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:11:24 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/09 13:11:26 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	norminette_de_mon_coeur(t_redraw *coord, int *x, int *y)
{
	*x = coord->up;
	*y = coord->left;
}

void	cpy_map_to_redraw(t_pos *pos, t_redraw *coord, char **redraw)
{
	int	x;
	int	y;

	norminette_de_mon_coeur(coord, &x, &y);
	while (x <= coord->down)
	{
		while (y <= coord->right)
		{
			if (x < 0 || y < 0)
				redraw[coord->x][coord->y] = '0';
			else if ((x >= pos->n || y >= pos->lanesize)
				&& (coord->x < 9 && coord->y < 13))
				redraw[coord->x][coord->y] = '0';
			else if ((x >= 0 || y >= 0) && (coord->x < 9 && coord->y < 13))
				redraw[coord->x][coord->y] = pos->map[x][y];
			y++;
			coord->y++;
		}
		redraw[coord->x][coord->y++] = '\0';
		y = coord->left;
		coord->y = 0;
		x++;
		coord->x++;
	}
	redraw[coord->x] = NULL;
}

void	format_redraw(t_redraw *coord, int *x, int *y)
{
	coord->up = *y - 4;
	coord->down = *y + 4;
	coord->left = *x - 6;
	coord->right = *x + 6;
}

void	where_is_charlie_xy(t_pos *pos, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pos->map[i])
	{
		while (pos->map[i][j])
		{
			if (pos->map[i][j] == 'P')
			{
				*x = i;
				*y = j;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	redraw(t_pos *pos)
{
	int			i;
	int			x;
	int			y;
	t_redraw	coord;

	i = 0;
	x = 0;
	y = 0;
	if (pos->redraw)
		free_map(pos->redraw);
	pos->redraw = (char **)ft_calloc(10, sizeof(char *));
	while (i < 9)
		pos->redraw[i++] = (char *)ft_calloc(14, sizeof(char));
	where_is_charlie_xy(pos, &y, &x);
	format_redraw(&coord, &x, &y);
	coord.x = 0;
	coord.y = 0;
	cpy_map_to_redraw(pos, &coord, pos->redraw);
}
