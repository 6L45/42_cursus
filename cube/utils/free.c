/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:27:55 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:27:57 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	close_img_win(t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_image(var->mlx, var->hiero);
	mlx_destroy_image(var->mlx, var->chariot);
	mlx_destroy_image(var->mlx, var->hermit);
	mlx_destroy_image(var->mlx, var->world);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var->plyer);
	free(var->cast_len);
	ft_free_char_array(var->map);
	exit(0);
}

void	ft_free_char_array(char **char_array)
{
	int		i;

	if (!char_array)
		return ;
	i = 0;
	while (char_array[i])
		free(char_array[i++]);
	free(char_array);
}

void	free_and_quit(t_fd_read *fdres, int quit)
{
	int	i;

	i = 0;
	while (fdres->values[i])
	{
		free(fdres->values[i]);
		i++;
	}
	if (fdres->no)
		free(fdres->no);
	if (fdres->so)
		free(fdres->so);
	if (fdres->we)
		free(fdres->we);
	if (fdres->ea)
		free(fdres->ea);
	if (fdres->f)
		free(fdres->f);
	if (fdres->c)
		free(fdres->c);
	free(fdres->values);
	if (fdres->map)
		ft_free_char_array(fdres->map);
	if (quit)
		exit(EXIT_FAILURE);
}
