/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:07:08 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 20:07:10 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	xpm__if_bad_size_exit(t_fd_read *fdres, t_vars *var,
				int i, char *texture)
{
	if (i != XPM_WIDTH * XPM_HEIGHT)
	{
		printf("%s bad size\n", texture);
		free_and_quit(fdres, 0);
		close_img_win(var);
	}
}

void	err_on_xpm_exit(t_fd_read *fdres, t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var->plyer);
	free(var->cast_len);
	ft_free_char_array(var->map);
	free_and_quit(fdres, 1);
}

void	xpm_size_checker(t_fd_read *fdres, t_vars *var)
{
	int	i;

	i = 0;
	while (var->fd_no[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "north texture");
	i = 0;
	while (var->fd_so[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "south texture");
	i = 0;
	while (var->fd_we[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "west texture");
	i = 0;
	while (var->fd_ea[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "east texture");
}
