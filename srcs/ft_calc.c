/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:47:53 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/04/30 14:55:28 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		ft_get_thread_id(t_data data)
{
	pthread_t	s;
	int			i;

	i = 0;
	s = pthread_self();
	while (data.t[i] != s)
		i++;
	return (i);
}

void	*ft_calc(void *param)
{
	t_coord		b;
	double		a;
	t_data		data;

	data = *(t_data*)param;
	data.wolf.x = ft_get_thread_id(data);
	a = data.wolf.orientation + 90 - FOV / 2 + data.wolf.angle * data.wolf.x;
	while (data.wolf.x < IMG_W)
	{
		b.x = data.wolf.pos.x - RAY_LEN * cos(PI2 * (a / 360));
		b.y = data.wolf.pos.y - RAY_LEN * sin(PI2 * (a / 360));
		ft_cast_sky_ray(&data, b);
		ft_cast_ray(&data, b, a);
		a += data.wolf.angle * NB_THREADS;
		data.wolf.x += NB_THREADS;
	}
	pthread_exit(0);
}

int		ft_calc_col_height(t_wolf *wolf, t_coord p, double a)
{
	int		h;

	h = WALL_H / (cos(PI2 * (fabs(wolf->orientation + 90 - a) / 360)) * \
		sqrt(ft_fpow(wolf->pos.x - p.x, 2.0) + ft_fpow(wolf->pos.y - p.y, 2.0))\
		) * wolf->screen_dist;
	return (h);
}
