/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:13:56 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/23 17:26:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		ft_check_coord(t_coord a, t_coord b, t_wolf wolf)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	else if (a.x < 0 || a.y < 0)
		return (1);
	else if (a.x > wolf.width * WALL_W || a.y > wolf.height * WALL_W)
		return (1);
	return (0);
}

int		ft_check_coord_sky(t_coord a, t_wolf wolf)
{
	if (a.x < WALL_W || a.y < WALL_W)
		return (1);
	else if (a.x > (wolf.width - 1) * WALL_W || a.y > (wolf.height - 1) * \
																		WALL_W)
		return (1);
	return (0);
}

int		ft_trace(t_data *data, t_coord p, t_coord tab, double a)
{
	t_wolf		*wolf;
	int			i;

	i = -1;
	wolf = &data->wolf;
	wolf->col_h = 0;
	tab.x /= WALL_W;
	tab.y /= WALL_W;
	if (!ft_check_coord(p, wolf->pos, *wolf) && wolf->map[tab.y][tab.x] != 0)
	{
		wolf->col_h = ft_calc_col_height(wolf, p, a);
		wolf->col_h -= wolf->col_h % 2;
		i = CENTER_Y - wolf->col_h / 2;
		while (++i < IMG_H)
			ft_putpixel(&data->win, i, data->wolf.x, ft_getcolor(i, \
														wolf->col_h, p, data));
	}
	if (wolf->col_h == 0)
		return (0);
	return (1);
}

void	ft_cast_ray(t_data *data, t_coord d, double a)
{
	t_ray		*ray;
	t_coord		s;

	s = data->wolf.pos;
	ray = &data->wolf.ray;
	ft_init_ray(ray, &s, d);
	while (1)
	{
		if (ft_trace(data, s, s, a) || ft_check_coord(s, d, data->wolf))
			break ;
		ray->e2 = ray->err;
		if (ray->e2 > -ray->dx)
		{
			ray->err -= ray->dy;
			s.x += ray->sx;
		}
		if (ray->e2 < ray->dy)
		{
			ray->err += ray->dx;
			s.y += ray->sy;
		}
	}
}

void	ft_cast_sky_ray(t_data *data, t_coord d)
{
	t_ray		*ray;
	t_coord		s;

	s = data->wolf.skypos;
	ray = &data->wolf.ray;
	ft_init_ray(ray, &s, d);
	while (1)
	{
		if (ft_check_coord_sky(s, data->wolf))
		{
			ft_draw_sky(&data->win, &data->wolf, data->wolf.x, s);
			break ;
		}
		ray->e2 = ray->err;
		if (ray->e2 > -ray->dx)
		{
			ray->err -= ray->dy;
			s.x += ray->sx;
		}
		if (ray->e2 < ray->dy)
		{
			ray->err += ray->dx;
			s.y += ray->sy;
		}
	}
}
