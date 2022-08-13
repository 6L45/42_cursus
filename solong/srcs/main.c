/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 22:06:00 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/07 22:06:02 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_img_win(t_pos *pos)
{
	free_map(pos->map);
	free_map(pos->redraw);
	mlx_destroy_image(pos->vars->mlx, pos->char_sprite);
	mlx_destroy_image(pos->vars->mlx, pos->char_wall);
	mlx_destroy_image(pos->vars->mlx, pos->char_door);
	mlx_destroy_image(pos->vars->mlx, pos->char_open);
	mlx_destroy_window(pos->vars->mlx, pos->vars->win);
	exit(0);
}

int	render_next_frame(t_pos *pos)
{
	mlx_clear_window(pos->vars->mlx, pos->vars->win);
	map_render(pos);
	if (pos->endgame)
		close_img_win(pos);
	return (1);
}

int	key_hook(int key, t_pos *pos)
{
	static int	nbr = 0;
	int			lstmv;

	lstmv = nbr;
	where_is_charlie(pos);
	if (key == 53)
		close_img_win(pos);
	if (!pos->endgame)
	{
		action_mvt(key, pos, &nbr);
		if (nbr != lstmv)
		{
			ft_putnbr(nbr);
			write(1, "\n", 1);
		}
	}
	return (0);
}

void	so_long_magic(t_pos *pos)
{
	pos->char_sprite = mlx_xpm_file_to_image(pos->vars->mlx,
			"sprites/result.xpm",
			&pos->img_width, &pos->img_height);
	pos->char_wall = mlx_xpm_file_to_image(pos->vars->mlx,
			"sprites/wall.xpm",
			&pos->img_width, &pos->img_height);
	pos->char_plant = mlx_xpm_file_to_image(pos->vars->mlx,
			"sprites/plant.xpm",
			&pos->img_width, &pos->img_height);
	pos->char_door = mlx_xpm_file_to_image(pos->vars->mlx,
			"sprites/door.xpm",
			&pos->img_width, &pos->img_height);
	pos->char_open = mlx_xpm_file_to_image(pos->vars->mlx,
			"sprites/open_door.xpm",
			&pos->img_width, &pos->img_height);
	mlx_key_hook(pos->vars->win, key_hook, pos);
	mlx_loop_hook(pos->vars->mlx, render_next_frame, pos);
	mlx_hook(pos->vars->win, 17, 1L << 17, close_img_win, pos);
	mlx_loop(pos->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_vars	vars;
	t_pos	pos;
	int		lanesize;
	int		n;

	if (argc == 2)
	{
		arg_receiver(&pos, &lanesize, &n, argv[1]);
		if (!pos.map || !lane_checker(pos.map))
			exit (0);
		pos_init(&pos);
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 13 * 64, 9 * 64, "So long");
		img.img = mlx_new_image(vars.mlx, 13 * 64, 9 * 64);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		pos.img = &img;
		pos.vars = &vars;
		so_long_magic(&pos);
	}
	return (0);
}
