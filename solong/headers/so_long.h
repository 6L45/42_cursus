/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 22:12:40 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/07 22:12:42 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

typedef enum e_direct
{
	UP = 1,
	DOWN,
	RIGHT,
	LEFT
}				t_direct;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_redraw
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	x;
	int	y;
}				t_redraw;

typedef struct s_pos
{
	t_data		*img;
	t_vars		*vars;
	void		*char_sprite;
	void		*char_wall;
	void		*char_plant;
	void		*char_door;
	void		*char_open;
	int			x;
	int			y;
	int			plants;
	int			endgame;
	int			img_width;
	int			img_height;
	int			lanesize;
	int			n;
	char		**map;
	char		**redraw;
}				t_pos;

void	arg_receiver(t_pos *pos, int *lanesize, int *n, char *argv);
void	where_is_charlie(t_pos *pos);
void	free_map(char **map);
void	map_render(t_pos *pos);
void	*ft_calloc(size_t count, size_t size);
void	action_mvt(int key, t_pos *pos, int *nbr);
int		lane_checker(char **map);
size_t	ft_strlen(char *str);
int		lane_lenght(char *buf);
void	free_map(char **map);
short	map_checker(char *buf, int *lastlanelen, int *n);
void	display_prep(t_pos *pos);
int		map_adjustment(t_pos *pos, int mvt, int *nbr);
void	error_map(void);
int		plants_counter(t_pos *pos);
void	ft_putnbr(int nbr);
void	pos_init(t_pos *pos);
int		elements_count(char *buf);
void	redraw(t_pos *pos);
void	where_is_charlie_redraw(t_pos *pos);

#endif
