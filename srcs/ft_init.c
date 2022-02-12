/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 15:33:26 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 15:29:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_init_ray(t_ray *ray, t_coord *a, t_coord b)
{
	ray->dx = abs(b.x - a->x);
	ray->sx = a->x < b.x ? 1 : -1;
	ray->dy = abs(b.y - a->y);
	ray->sy = a->y < b.y ? 1 : -1;
	ray->err = (ray->dx > ray->dy) ? ray->dx : -ray->dy / 2;
	ray->e2 = ray->err;
}

void	ft_init_data(t_data *data)
{
	t_wolf	*wolf;
	t_win	*win;

	win = &data->win;
	wolf = &data->wolf;
	wolf->screen_dist = CENTER_X / tan(PI2 / (360 / (FOV / 2)));
	wolf->angle = (double)FOV / (double)IMG_W;
	wolf->pos.x = -1;
	wolf->pos.y = -1;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_W, WIN_H, "Wolf 3D");
	win->img = mlx_new_image(win->mlx, IMG_W, IMG_H);
	win->data = mlx_get_data_addr(win->img, &win->bpp, &win->linelen, \
																&win->endian);
}

void	ft_init_threads(t_data *data, t_wolf *wolf)
{
	int		i;

	i = -1;
	while (++i < NB_THREADS)
	{
		wolf->x = 0;
		if (pthread_create(&data->t[i], NULL, ft_calc, (void *)data))
			ft_error(data, 4);
	}
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_join(data->t[i], NULL) != 0)
			ft_error(data, 5);
}
