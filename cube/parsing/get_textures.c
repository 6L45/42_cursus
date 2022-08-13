/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:02:12 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 20:02:14 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	fdno_init(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->hiero = mlx_xpm_file_to_image(var->mlx, fdres->no,
			&width, &height);
	if (!var->hiero)
	{
		ft_putstr_fd("NO texture error\n", 2);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_no = (int *)mlx_get_data_addr(var->hiero, &var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

static void	fdso_init(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->world = mlx_xpm_file_to_image(var->mlx, fdres->so,
			&width, &height);
	if (!var->world)
	{
		ft_putstr_fd("SO texture error\n", 2);
		mlx_destroy_image(var->mlx, var->hermit);
		mlx_destroy_image(var->mlx, var->chariot);
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_so = (int *)mlx_get_data_addr(var->world,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

static void	fdwe_init(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->chariot = mlx_xpm_file_to_image(var->mlx, fdres->we,
			&width, &height);
	if (!var->chariot)
	{
		ft_putstr_fd("WE texture error\n", 2);
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_we = (int *)mlx_get_data_addr(var->chariot,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

static void	fdea_init(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->hermit = mlx_xpm_file_to_image(var->mlx, fdres->ea,
			&width, &height);
	if (!var->hermit)
	{
		ft_putstr_fd("EA texture error\n", 2);
		mlx_destroy_image(var->mlx, var->chariot);
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_ea = (int *)mlx_get_data_addr(var->hermit,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	get_textures(t_fd_read *fdres, t_vars *var)
{
	int	width;
	int	height;

	width = XPM_WIDTH;
	height = XPM_HEIGHT;
	fdno_init(fdres, var, width, height);
	fdwe_init(fdres, var, width, height);
	fdea_init(fdres, var, width, height);
	fdso_init(fdres, var, width, height);
	xpm_size_checker(fdres, var);
	floor_and_ceiling_init(fdres, var);
}
