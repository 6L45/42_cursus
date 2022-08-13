/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:46:05 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:46:10 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	up(t_key key_var, t_vars *var)
{
	if (var->map[(int)(var->plyer->x + var->dirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(var->dirx * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + var->diry * key_var.movespeed)] == '0')
		var->plyer->y += (float)(var->diry * key_var.movespeed);
}

void	down(t_key key_var, t_vars *var)
{
	if (var->map[(int)(var->plyer->x - var->dirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x -= var->dirx * key_var.movespeed;
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y - var->diry * key_var.movespeed)] == '0')
		var->plyer->y -= var->diry * key_var.movespeed;
}

void	strafe_left(t_key key_var, t_vars *var)
{
	key_var.tmpdirx = var->dirx * cos(90 * (M_PI / 180))
		- var->diry * sin(90 * (M_PI / 180));
	key_var.tmpdiry = key_var.olddirx * sin(90 * (M_PI / 180))
		+ var->diry * cos(90 * (M_PI / 180));
	if (var->map[(int)(var->plyer->x + key_var.tmpdirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(key_var.tmpdirx * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + key_var.tmpdiry * key_var.movespeed)] == '0')
		var->plyer->y += (float)(key_var.tmpdiry * key_var.movespeed);
}

void	strafe_right(t_key key_var, t_vars *var)
{
	key_var.tmpdirx = var->dirx * cos(-90 * (M_PI / 180))
		- var->diry * sin(-90 * (M_PI / 180));
	key_var.tmpdiry = key_var.olddirx * sin(-90 * (M_PI / 180))
		+ var->diry * cos(-90 * (M_PI / 180));
	if (var->map[(int)(var->plyer->x + key_var.tmpdirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(key_var.tmpdirx * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + key_var.tmpdiry * key_var.movespeed)] == '0')
		var->plyer->y += (float)(key_var.tmpdiry * key_var.movespeed);
}
