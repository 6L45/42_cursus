/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:00:38 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/05 18:00:40 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>

enum e_type
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
	SET,
	GET,
	VERT,
	HOR,
	PLUS,
	MINUS
};

typedef struct s_key
{
	double	olddirx;
	double	oldplanex;
	double	rotspeed;
	double	movespeed;
	double	tmpdirx;
	double	tmpdiry;
}				t_key;

typedef struct s_ray
{
	int		color;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		hit;
	int		side;
	int		pitch;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texx;
	int		texy;
	double	posx;
	double	posy;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
	double	step;
	double	texpos;
}				t_ray;

typedef struct s_plyer
{
	float	x;
	float	y;
	float	orientation;
}				t_plyer;

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
	t_plyer	*plyer;
	t_data	*img;
	float	*cast_len;
	char	**map;
	void	*hiero;
	void	*chariot;
	void	*hermit;
	void	*world;
	int		*fd_no;
	int		*fd_so;
	int		*fd_we;
	int		*fd_ea;
	int		floor[3];
	int		ceiling[3];
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}				t_vars;

typedef struct s_fd_read
{
	char	**values;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
}				t_fd_read;

typedef struct s_lst_check
{
	int		index;
	int		(*func)(t_fd_read *fdres, char *line, int l, int to_value);
	int		to_value;
}				t_lst_check;

# define S_WIDTH 1200.0
# define S_HEIGHT 700.0
# define UP 122
# define LEFT 113
# define RIGHT 100
# define DOWN 115
# define R_ROT 65363
# define L_ROT 65361
# define XPM_WIDTH 64
# define XPM_HEIGHT 64

/*PARSING --------------------------------------------------------------------*/
/* ************************************************************************** */

// ERR_OUTPUT.C
void	err_map(t_fd_read *fdres);

// FILE_CHECKER.C
void	file_checker(t_fd_read *fdres, char **file_content, int i, int l);

// FILE_HANDLER.C
void	file_handler(t_fd_read *fdres, char *file_name);
int		texture_path_value_checker(char *line);

// FT_CHECK.C
void	first_last_line_checker(t_fd_read *fdres, int i);
void	space_checker(t_fd_read *fdres, int i, int j);
void	map_scanning(t_fd_read *fdres, int i, int j);
void	last_carac_checker(t_fd_read *fdres, int i, int j);
void	first_carac_checker(t_fd_read *fdres, int i);

// GET_TEXTURES.C
void	get_textures(t_fd_read *fdres, t_vars *var);

// PARSE_UTILS.C
char	*str_char_cat(char *buf, char c);
int		max_len_in_array(char **array);
int		file_is_cub(char *file_name);
void	cp_char_array_with_filler(char ***dest, char **src, int i, int *endmap);

// TEXTURE_CHECKER.C
int		fill_texture_address_fdres(t_fd_read *fdres, char *line, int i, int l);

// TEXTURE_UTILS.C
int		end_line_checker(char *line, int l);
int		start_line_checker(char *line, int *j, int l);
int		init_i(char *line, int start);
int		digit_conditions_check(char *values, int i, int j);
int		digit_value_end_line_checker(char *line);

// XPM_CHECKER.C
void	xpm_size_checker(t_fd_read *fdres, t_vars *var);
void	err_on_xpm_exit(t_fd_read *fdres, t_vars *var);

/*SRCS -----------------------------------------------------------------------*/
/* ************************************************************************** */

// DRAWING.C
void	draw_wall(t_ray *cast, t_vars *var, int x);
void	draw_floor(t_ray *cast, t_vars *var, int x);
void	draw_ceiling(t_ray *cast, t_vars *var, int x);

// INIT_STR.C
void	var_plyer_init(t_vars *var, t_fd_read *fdres);
void	initfdres(t_fd_read *fdres);
void	floor_and_ceiling_init(t_fd_read *fdres, t_vars *var);

// KEY_PRESS.C
int		key_press(int key, t_vars *var);

// MINIMAP.C
void	plyrpos(t_vars *var);
void	minimap(t_vars *var);

// MVT.C
void	strafe_right(t_key key_var, t_vars *var);
void	strafe_left(t_key key_var, t_vars *var);
void	down(t_key key_var, t_vars *var);
void	up(t_key key_var, t_vars *var);

// RAYCAST.C
void	rayscasting(t_vars *var);

// RENDER.C
int		render_next_frame(t_vars *var);
void	set_texture(t_ray *cast);
void	set_drawing_area(t_ray *cast);

// SCREEN_POS.C
void	look_left(t_vars *var);
void	look_right(t_vars *var);
void	look_down(t_vars *var);
void	look_up(t_vars *var);

// SRCS_UTILS.C
void	cp_char_array(char ***dest, char **src);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	arrays_size_check(t_fd_read *fdres, t_vars *var,
			char ***ar1, char ***ar2);

/*UTILS ----------------------------------------------------------------------*/
/* ************************************************************************** */

// FREE.C
void	free_and_quit(t_fd_read *fdres, int quit);
void	ft_free_char_array(char **char_array);
int		close_img_win(t_vars *var);

// FT_COLOR.C
int		get_b(int trgb);
int		get_g(int trgb);
int		get_r(int trgb);
int		get_t(int trgb);
int		create_trgb(int t, int r, int g, int b);

// UTILS.C
void	err_print(t_fd_read *fdres, char *expected_value, int l);
int		empty_line(char *line);
int		authorized_char(char c);
int		player_set(int status);

#endif
