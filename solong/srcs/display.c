/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:51:19 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/08 14:51:21 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	wall_display(t_pos *pos, int x, int y)
{
	mlx_put_image_to_window(pos->vars->mlx, pos->vars->win,
		pos->char_wall, y * 64, x * 64);
}

void	player_display(t_pos *pos)
{
	if (pos->endgame)
	{
		if (pos->endgame == UP)
			pos->x -= 64;
		if (pos->endgame == DOWN)
			pos->x += 64;
		if (pos->endgame == RIGHT)
			pos->y += 64;
		if (pos->endgame == LEFT)
			pos->y -= 64;
	}
	mlx_put_image_to_window(pos->vars->mlx, pos->vars->win,
		pos->char_sprite, 6 * 64, 4 * 64);
}

void	plants_display(t_pos *pos, int x, int y)
{
	mlx_put_image_to_window(pos->vars->mlx, pos->vars->win,
		pos->char_plant, y * 64, x * 64);
}

void	exit_display(t_pos *pos, int x, int y)
{
	int	plants;

	plants = plants_counter(pos);
	if (!plants)
	{
		mlx_put_image_to_window(pos->vars->mlx, pos->vars->win,
			pos->char_open, y * 64, x * 64);
	}
	else
		mlx_put_image_to_window(pos->vars->mlx, pos->vars->win,
			pos->char_door, y * 64, x * 64);
}

void	map_render(t_pos *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	display_prep(pos);
	while (pos->redraw[x])
	{
		while (pos->redraw[x][y])
		{
			if (pos->redraw[x][y] == '1')
				wall_display(pos, x, y);
			if (pos->redraw[x][y] == 'P')
				player_display(pos);
			if (pos->redraw[x][y] == 'C')
				plants_display(pos, x, y);
			if (pos->redraw[x][y] == 'E')
				exit_display(pos, x, y);
			y++;
		}
		y = 0;
		x++;
	}
}
