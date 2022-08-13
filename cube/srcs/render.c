/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:59:22 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 20:59:24 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_drawing_area(t_ray *cast)
{
	if (cast->side == 0)
		cast->perpwalldist = (cast->sidedistx - cast->deltadistx);
	else
		cast->perpwalldist = (cast->sidedisty - cast->deltadisty);
	cast->lineheight = (int)(S_HEIGHT / cast->perpwalldist);
	cast->drawstart = -cast->lineheight / 2 + S_HEIGHT / 2 + cast->pitch;
	if (cast->drawstart < 0)
		cast->drawstart = 0;
	cast->drawend = cast->lineheight / 2 + S_HEIGHT / 2 + cast->pitch;
	if (cast->drawend >= S_HEIGHT)
		cast->drawend = S_HEIGHT - 1;
}

void	set_texture(t_ray *cast)
{
	if (cast->side == 0)
		cast->wallx = cast->posy + cast->perpwalldist * cast->raydiry;
	else
		cast->wallx = cast->posx + cast->perpwalldist * cast->raydirx;
	cast->wallx -= floor((cast->wallx));
	cast->texx = (int)(cast->wallx * (double)(XPM_WIDTH));
	if (cast->side == 0 && cast->raydirx > 0)
		cast->texx = XPM_WIDTH - cast->texx - 1;
	if (cast->side == 1 && cast->raydiry < 0)
		cast->texx = XPM_WIDTH - cast->texx - 1;
	cast->step = 1.0 * XPM_HEIGHT / cast->lineheight;
	cast->texpos = (cast->drawstart - cast->pitch
			- S_HEIGHT / 2 + cast->lineheight / 2) * cast->step;
}

int	render_next_frame(t_vars *var)
{
	rayscasting(var);
	minimap(var);
	plyrpos(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
	return (1);
}
