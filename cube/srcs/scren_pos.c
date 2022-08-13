/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scren_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:51:04 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:51:06 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	look_up(t_vars *var)
{
	var->dirx = -1;
	var->diry = 0;
	var->planex = 0.0;
	var->planey = 0.66;
}

void	look_down(t_vars *var)
{
	var->dirx = 1;
	var->diry = 0;
	var->planex = 0;
	var->planey = -0.66;
}

void	look_right(t_vars *var)
{
	var->diry = 1;
	var->dirx = 0;
	var->planex = 0.66;
	var->planey = 0;
}

void	look_left(t_vars *var)
{
	var->diry = -1;
	var->dirx = 0;
	var->planex = -0.66;
	var->planey = 0;
}
