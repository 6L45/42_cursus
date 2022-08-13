/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:51:53 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:51:55 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	cube_drawing(t_vars *var, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * 8 + 1;
	while (i < (x * 8 + 1) + 6)
	{
		j = y * 8;
		while (j < (y * 8 + 1) + 6)
		{
			my_mlx_pixel_put(var->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_vars *var)
{
	int	y;
	int	x;

	y = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (var->map[y][x] == '1')
				cube_drawing(var, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	plyrpos(t_vars *var)
{
	my_mlx_pixel_put(var->img, 8 * var->plyer->y,
		8 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y + 1,
		8 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y + 1,
		8 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y + 1,
		8 * var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y - 1,
		8 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y - 1,
		8 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y - 1,
		8 * var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y,
		8 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 8 * var->plyer->y,
		8 * var->plyer->x - 1, 0x00FFFFFF);
}
