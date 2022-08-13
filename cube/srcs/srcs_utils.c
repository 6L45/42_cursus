/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:15:13 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 20:15:14 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	arrays_size_check(t_fd_read *fdres, t_vars *var,
			char ***ar1, char ***ar2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*ar1)[i])
		i++;
	while ((*ar2)[j])
		j++;
	if (i != 3 || j != 3)
	{
		if (i != 3)
			ft_putstr_fd("floor values : error 3 numbers expected\n", 2);
		else
			ft_putstr_fd("ceiling values : error 3 numbers expected\n", 2);
		ft_free_char_array((*ar1));
		ft_free_char_array((*ar2));
		mlx_destroy_image(var->mlx, var->hermit);
		mlx_destroy_image(var->mlx, var->chariot);
		mlx_destroy_image(var->mlx, var->hiero);
		mlx_destroy_image(var->mlx, var->world);
		err_on_xpm_exit(fdres, var);
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cp_char_array(char ***dest, char **src)
{
	int	i;
	int	size;
	int	empty;

	i = 0;
	empty = 0;
	size = 0;
	while (empty_line(src[empty]))
		empty++;
	while (src[empty + i])
		i++;
	(*dest) = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (src[empty + i])
	{
		if (empty_line(src[empty + i]))
			return ;
		(*dest)[i] = ft_strdup(src[empty + i]);
		i++;
		size++;
	}
}
