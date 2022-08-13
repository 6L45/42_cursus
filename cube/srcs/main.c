/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:31 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:33 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_fd_read	fdres;
	t_data		img;
	t_vars		var;

	if (argc != 2)
		return (1);
	initfdres(&fdres);
	file_handler(&fdres, argv[1]);
	var_plyer_init(&var, &fdres);
	var.img = &img;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, S_WIDTH, S_HEIGHT, "Cube3D");
	img.img = mlx_new_image(var.mlx, S_WIDTH, S_HEIGHT);
	get_textures(&fdres, &var);
	free_and_quit(&fdres, 0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mlx_hook(var.win, 2, 1L << 0, key_press, &var);
	mlx_loop_hook(var.mlx, render_next_frame, &var);
	mlx_hook(var.win, 17, 1L << 17, close_img_win, &var);
	mlx_loop(var.mlx);
	return (0);
}
