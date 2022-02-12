/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:14:31 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/23 14:54:49 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WIN_W 1200
# define WIN_H 800
# define IMG_W WIN_W
# define IMG_H WIN_H
# define CENTER_X 600
# define CENTER_Y 400
# define FOV 60
# define WALL_H 91
# define WALL_W 64
# define CAM_H 45
# define RAY_LEN 10000
# define PI2 6.283158
# define NB_TEXTURES 16
# define NB_THREADS 16
# define FLOOR_COLOR 5066061
# define SPEED 10.0
# define SKY "textures/sky.xpm"

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_ray
{
	int			dx;
	int			dy;
	int			err;
	int			e2;
	int			sx;
	int			sy;
}				t_ray;

typedef	struct	s_img
{
	int			width;
	int			height;
	int			bpp;
	int			endian;
	int			linelen;
	char		*data;
	void		*img;
}				t_img;

typedef struct	s_wolf
{
	double		angle;
	double		orientation;
	char		**size;
	int			**map;
	int			col_h;
	int			height;
	int			screen_dist;
	int			width;
	int			sky;
	int			x;
	t_img		skybox;
	t_img		textures[NB_TEXTURES];
	t_ray		ray;
	t_coord		pos;
	t_coord		skypos;
}				t_wolf;

typedef struct	s_win
{
	int			bpp;
	int			endian;
	int			linelen;
	char		*data;
	void		*img;
	void		*mlx;
	void		*win;
}				t_win;

typedef struct	s_data
{
	t_win		win;
	t_wolf		wolf;
	pthread_t	t[NB_THREADS];
}				t_data;

double			ft_calc_angle(int orientation);
void			*ft_calc(void *param);
void			ft_get_textures(t_data *data, t_win *win, t_img *textures);
void			ft_getmap(t_data *data, t_wolf *wolf, char *file);
void			ft_putpixel(t_win *win, int y, int x, int color);
void			ft_init_ray(t_ray *ray, t_coord *a, t_coord b);
void			ft_cast_ray(t_data *data, t_coord d, double a);
void			ft_init_threads(t_data *data, t_wolf *wolf);
void			ft_cast_sky_ray(t_data *data, t_coord d);
void			ft_draw_sky(t_win *win, t_wolf *wolf, int j, t_coord p);
void			ft_error(t_data *data, int error);
void			ft_rotate(t_data *data, int key);
void			ft_move(t_data *data, double s);
void			ft_init_data(t_data *data);
void			ft_refresh(t_data *data);
int				ft_calc_col_height(t_wolf *wolf, t_coord p, double a);
int				ft_getcolor(int i, int col_h, t_coord p, t_data *data);
int				ft_keyhook(int key, void *param);
int				ft_exit(void *param);

#endif
