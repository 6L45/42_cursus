/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:48:44 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:48:46 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_ceiling(t_ray *cast, t_vars *var, int x)
{
	int	i;

	i = 0;
	while (i < cast->drawstart + cast->pitch)
	{
		my_mlx_pixel_put(var->img, x, i,
			create_trgb(255,
				var->ceiling[0], var->ceiling[1], var->ceiling[2]));
		i++;
	}
}

void	draw_floor(t_ray *cast, t_vars *var, int x)
{
	while (cast->drawstart < S_HEIGHT)
	{
		my_mlx_pixel_put(var->img, x, cast->drawstart,
			create_trgb(255, var->floor[0], var->floor[1], var->floor[2]));
		cast->drawstart++;
	}
}

void	draw_wall(t_ray *cast, t_vars *var, int x)
{
	while (cast->drawstart < cast->drawend)
	{
		cast->texy = (int)cast->texpos & (XPM_HEIGHT - 1);
		cast->texpos += cast->step;
		if (cast->side)
		{
			if (cast->stepy == 1)
				cast->color = var->fd_ea[XPM_HEIGHT * cast->texy + cast->texx];
			else
				cast->color = var->fd_we[XPM_HEIGHT * cast->texy + cast->texx];
		}
		else if (!cast->side)
		{
			if (cast->stepx == 1)
				cast->color = var->fd_so[XPM_HEIGHT * cast->texy + cast->texx];
			else
				cast->color = var->fd_no[XPM_HEIGHT * cast->texy + cast->texx];
		}
		else
			cast->color = 0x0FFFFFF;
		my_mlx_pixel_put(var->img, x, cast->drawstart,
			create_trgb(255,
				get_r(cast->color), get_g(cast->color), get_b(cast->color)));
		cast->drawstart++;
	}
}
