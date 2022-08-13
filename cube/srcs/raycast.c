/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:54:54 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:54:56 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	cam_orientation_setup(t_ray *cast, t_vars *var, int x)
{
	static const double	cam_shift = 2.0 / S_WIDTH;

	cast->camerax = -1 + (x * cam_shift);
	cast->raydirx = var->dirx + var->planex * cast->camerax;
	cast->raydiry = var->diry + var->planey * cast->camerax;
	cast->mapx = (int)cast->posx;
	cast->mapy = (int)cast->posy;
	if (cast->raydirx == 0)
		cast->deltadistx = 1e30;
	else
		cast->deltadistx = fabs((1 / cast->raydirx));
	if (cast->raydiry == 0)
		cast->deltadisty = 1e30;
	else
		cast->deltadisty = fabs((1 / cast->raydiry));
}

static void	vector_step_setup(t_ray *cast)
{
	if (cast->raydirx < 0)
	{
		cast->stepx = -1;
		cast->sidedistx = (cast->posx - cast->mapx) * cast->deltadistx;
	}
	else
	{
		cast->stepx = 1;
		cast->sidedistx = (cast->mapx + 1.0 - cast->posx) * cast->deltadistx;
	}
	if (cast->raydiry < 0)
	{
		cast->stepy = -1;
		cast->sidedisty = (cast->posy - cast->mapy) * cast->deltadisty;
	}
	else
	{
		cast->stepy = 1;
		cast->sidedisty = (cast->mapy + 1.0 - cast->posy) * cast->deltadisty;
	}
}

static void	perform_dda(t_ray *cast, t_vars *var)
{
	while (cast->hit == 0)
	{
		if (cast->sidedistx < cast->sidedisty)
		{
			cast->sidedistx += cast->deltadistx;
			cast->mapx += cast->stepx;
			cast->side = 0;
		}
		else
		{
			cast->sidedisty += cast->deltadisty;
			cast->mapy += cast->stepy;
			cast->side = 1;
		}
		if (var->map[cast->mapx][cast->mapy] == '1')
			cast->hit = 1;
	}
}

void	rayscasting(t_vars *var)
{
	int		x;
	t_ray	cast;

	x = 0;
	cast.pitch = 100;
	cast.posx = var->plyer->x;
	cast.posy = var->plyer->y;
	while (x < S_WIDTH)
	{
		cam_orientation_setup(&cast, var, x);
		cast.hit = 0;
		vector_step_setup(&cast);
		perform_dda(&cast, var);
		set_drawing_area(&cast);
		set_texture(&cast);
		draw_ceiling(&cast, var, x);
		draw_wall(&cast, var, x);
		draw_floor(&cast, var, x);
		x++;
	}
}
