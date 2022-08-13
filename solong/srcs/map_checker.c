/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:51:43 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:51:45 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	elements_count(char *buf)
{
	int	player;
	int	plant;
	int	endgame;
	int	i;

	i = 0;
	player = 0;
	plant = 0;
	endgame = 0;
	while (buf[i])
	{
		if (buf[i] == 'P')
			player++;
		if (buf[i] == 'C')
			plant++;
		if (buf[i] == 'E')
			endgame++;
		i++;
	}
	if (player != 1 || plant == 0 || endgame == 0)
		return (0);
	return (1);
}

void	pos_init(t_pos *pos)
{
	pos->redraw = NULL;
	pos->img_width = 64;
	pos->img_height = 64;
	pos->endgame = 0;
}

int	not_allowed_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P'
			&& str[i] != 'C' && str[i] != 'E')
			error_map();
		i++;
	}
	return (1);
}

int	lane_checker(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!not_allowed_char(map[i]))
			return (0);
		i++;
	}
	return (1);
}
