/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:02:15 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 15:02:16 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	action_mvt(int key, t_pos *pos, int *nbr)
{
	if (key == 13 || key == 126)
	{
		if (map_adjustment(pos, UP, nbr))
			pos->y -= 64;
	}
	if (key == 0 || key == 123)
	{
		if (map_adjustment(pos, LEFT, nbr))
			pos->x -= 64;
	}
	if (key == 2 || key == 124)
	{
		if (map_adjustment(pos, RIGHT, nbr))
			pos->x += 64;
	}
	if (key == 1 || key == 125)
	{
		if (map_adjustment(pos, DOWN, nbr))
			pos->y += 64;
	}
}
