/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 21:01:08 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/05/01 16:45:41 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_calc_y(int or, t_coord *pos, t_coord *c, int s)
{
	if (or == 450.0 || (or == 455.0 && s != 1) || or == 445.0)
		c->x = sin(PI2 * (fmod(or, 360.0) / 360.0)) * SPEED * s * -1.0 + pos->x;
	else if (or == 630.0 || (or == 635.0 && s != -1) || or == 625.0)
		c->x = sin(PI2 * (fmod(or, 360.0) / 360.0)) * SPEED * s * -1.0 + pos->x;
	else if ((or == 540.0 || or == 545.0) && s == 1)
		c->x = sin(PI2 * (fmod(or - 180.0 + (or - 540.0), 360.0) / 360.0)) * \
														SPEED * 1.0 + pos->x;
	else if (or == 365.0)
		c->x = sin(PI2 * (fmod(or + 5, 360.0) / 360.0)) * SPEED * s * -1.0 + \
																		pos->x;
	else
		c->x = sin(PI2 * (fmod(or, 360.0) / 360.0)) * SPEED * s * -1.0 + pos->x;
}

void	ft_calc_x(int or, t_coord *pos, t_coord *c, int s)
{
	if (or == 450.0 || (or == 455.0 && s != 1) || or == 445.0)
		c->y = cos(PI2 / (360.0 / fmod(or - 5 * s, 360.0))) * SPEED * s + \
																		pos->y;
	else if (or == 630.0 || (or == 635.0 && s != -1) || or == 625.0)
		c->y = cos(PI2 / (360.0 / fmod(or + 5 * s, 360.0))) * SPEED * s + \
																		pos->y;
	else if ((or == 540.0 || or == 545.0) && s == 1)
		c->y = cos(PI2 / (360.0 / fmod(or - 180.0 + (540.0 - or), 360.0))) * \
														SPEED * -1.0 + pos->y;
	else
		c->y = cos(PI2 / (360.0 / fmod(or, 360.0))) * SPEED * s + pos->y;
}

void	ft_move(t_data *data, double s)
{
	t_wolf	*wolf;
	t_coord	c;

	wolf = &data->wolf;
	ft_calc_x(wolf->orientation, &wolf->pos, &c, s);
	ft_calc_y(wolf->orientation, &wolf->pos, &c, s);
	if (wolf->map[(c.y + 5) / WALL_W][(c.x + 5) / WALL_W] == 0 && \
		wolf->map[(c.y - 5) / WALL_W][(c.x - 5) / WALL_W] == 0 && \
		wolf->map[(c.y - 5) / WALL_W][(c.x + 5) / WALL_W] == 0 && \
		wolf->map[(c.y + 5) / WALL_W][(c.x - 5) / WALL_W] == 0)
		wolf->pos = c;
	ft_refresh(data);
}

void	ft_rotate(t_data *data, int key)
{
	if (key == 124)
		data->wolf.orientation += 5.0;
	else
		data->wolf.orientation -= 5.0;
	if (data->wolf.orientation == 355.0)
		data->wolf.orientation = 715.0;
	if (data->wolf.orientation == 720.0)
		data->wolf.orientation = 360.0;
	ft_refresh(data);
}
