/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:21:55 by david             #+#    #+#             */
/*   Updated: 2024/09/05 11:48:41 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include "./libft/libft.h"
#include "./mlx_linux/mlx.h"
#include <math.h>
# include <sys/time.h>

#define RESW 1080
#define RESH 720

#define MULTIPLIER 64

#define ROT_MULTIPLIER 3.0
#define MOVE_SPEED_MULTIPLIER 5.0


typedef struct s_tt
{
	void		*img;
	char		*name;
	char		*addr;
	int			bpp;
	int			l_length;
	int			endian;
}				t_tt;

typedef struct s_mapdata
{
	char		**map;
	char		**tmp;
	int			after_txtr;
	int			map_start;
	int			map_end;
	int			height;
	int			length;
	int			fcolor;
	int			ccolor;
	t_tt		ntt;
	t_tt		wtt;
	t_tt		ett;
	t_tt		stt;
}				t_mapdata;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_tt		frame;
	t_mapdata	*map;
	double		posX;//player pos
	double		posY;
	double		dirX;
	double		dirY;
	double		sideDirX;
	double		sideDirY;
	double		planeX;//perpendicular to dir (at least while you're sober)
	double		planeY;
	double		time;
	double		oldTime;
	double		cameraX;
	double		moveSpeed;
	double		rotSpeed;
	int			rotation;
	int			w;
	int			a;
	int			s;
	int			d;
	t_img		current_frame;
	t_img		*textures;
}				t_data;

//general
t_data		*data(void);
// void		error_handle(int err, char *msg, t_data *game);
int			ft_strcmp(char *str1, char *str2);
// void		free_mtx(char **mtx);
void		print_matrix(char **cpy_file);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		getmatrix(char *file);
int			timern(void);
int		 	stop(int keycode);
void    	do_walk();
char    check_borders(int mapX, int mapY);
void    rotate_vector(double *x, double *y, double radians);
int close_win();
void    do_rotate();

//parsing
void	check_file(char *file, t_data **game);
int		check_line(char *file);
int		check_str(char *str);
void	mapline_add(t_data *game, char *line);
int		find_path(char *str, int i);
int		add_texture(char *file, t_data *game);
int		color_info(char *file, t_mapdata *map, t_data *game, int fl);
int		skip_spaces(char **file, char *start);
int		map_start(char *file);
int		read_map(char **file, t_data *game);
void	allct_map(char **map, t_data *game);
int		map_parse(t_mapdata *map);
int		renderLoop(void);
unsigned int	get_color(t_img *image, int x, int y);
//raycasting
void	calculus(char **map);
void	raycastLoop();
int		walk(int keycode);
void	camera();

#endif