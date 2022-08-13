/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:59:35 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:59:36 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_var_file_checker(char ***content, char **file_content)
{
	*content = ft_split(*file_content, '\n');
	free(*file_content);
}

static void	err_on_texture_exit(t_fd_read *fdres, char ***content)
{
	ft_free_char_array(*content);
	free_and_quit(fdres, 1);
}

static void	wrong_value_exit(t_fd_read *fdres, char ***content, int l, int i)
{
	ft_free_char_array(*content);
	err_print(fdres, fdres->values[l], i + 1);
}

static void	map_cpy_and_free_content(t_fd_read *fdres, char ***content, int i)
{
	int	endmap;

	cp_char_array_with_filler(&fdres->map, &(*content)[i], 0, &endmap);
	while ((*content)[endmap + i])
	{
		if (!empty_line((*content)[endmap + i]))
		{
			ft_putstr_fd("Error : unexpected value after map\n", 2);
			ft_free_char_array(*content);
			free_and_quit(fdres, 1);
		}
		i++;
	}
	ft_free_char_array(*content);
}

void	file_checker(t_fd_read *fdres, char **file_content, int i, int l)
{
	int		j;
	char	**content;

	init_var_file_checker(&content, file_content);
	while (content[i] && fdres->values[l])
	{
		j = 0;
		while (content[i][j] && content[i][j] > 0 && content[i][j] <= 32)
			j++;
		if (!content[i][j])
			;
		else if (!(ft_strncmp(fdres->values[l], &content[i][j],
				ft_strlen(fdres->values[l])))
			&& texture_path_value_checker(&content[i][j]))
		{
			if (!fill_texture_address_fdres(fdres, content[i], l, i))
				err_on_texture_exit(fdres, &content);
			l++;
		}
		else
			wrong_value_exit(fdres, &content, l, i);
		i++;
	}
	map_cpy_and_free_content(fdres, &content, i);
}
