/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 17:14:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/05/03 15:10:38 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_putpixel(t_win *win, int y, int x, int color)
{
	int		i;

	i = 0;
	if (x < IMG_W && y < IMG_H && x >= 0 && y >= 0)
	{
		i = win->linelen * y + x * (win->bpp / 8);
		win->data[i] = color & 0xff;
		win->data[++i] = color >> 8 & 0xff;
		win->data[++i] = color >> 16 & 0xff;
	}
}

int		ft_get_sky_color(t_wolf *wolf, int i, int j, t_coord p)
{
	if (p.x % wolf->skybox.width == 0 || p.x % wolf->skybox.width == WALL_W - 1\
				|| p.x == (wolf->width - 1) * WALL_W + 1)
		j = p.y % wolf->skybox.width;
	else
		j = p.x % wolf->skybox.width;
	j = (i * wolf->skybox.linelen) + (((double)j / (double)IMG_W) * \
														wolf->skybox.width) * 4;
	return (wolf->skybox.data[j] | wolf->skybox.data[j + 1] << 8 | \
												wolf->skybox.data[j + 2] << 16);
}

void	ft_draw_sky(t_win *win, t_wolf *wolf, int j, t_coord p)
{
	int		i;

	i = -1;
	while (++i < CENTER_Y)
		ft_putpixel(win, i, j, ft_get_sky_color(wolf, i, j, p));
}

int		ft_getcolor(int i, int col_h, t_coord p, t_data *data)
{
	int		j;
	int		tmp_i;
	int		obj;
	t_img	*img;

	obj = data->wolf.map[p.y / WALL_W][p.x / WALL_W];
	if (i > CENTER_Y + col_h / 2 - 1)
		return (FLOOR_COLOR);
	else
		img = &data->wolf.textures[obj - 1];
	tmp_i = i;
	i = (double)(i - (CENTER_Y - col_h / 2 + 1)) / col_h * img->height;
	if (p.x % img->width == 0 || p.x % img->width == 63)
		j = p.y % img->width;
	else
		j = p.x % img->width;
	j = img->linelen * i + j * (img->bpp / 8);
	return (img->data[j] | img->data[j + 1] << 8 | img->data[j + 2] << 16);
}

void	ft_get_textures(t_data *data, t_win *win, t_img textures[NB_TEXTURES])
{
	int		i;
	char	name[17];
	char	*nb;
	t_img	*s;

	s = &data->wolf.skybox;
	nb = NULL;
	i = -1;
	if (!(s->img = mlx_xpm_file_to_image(win->mlx, SKY, &s->width, &s->height)))
		ft_error(data, 8);
	s->data = mlx_get_data_addr(s->img, &s->bpp, &s->linelen, &s->endian);
	while (++i < NB_TEXTURES)
	{
		ft_bzero(name, 17);
		ft_strcat(name, "textures/");
		nb = ft_itoa(i + 1);
		ft_strcat(name, nb);
		free(nb);
		ft_strcat(name, ".xpm");
		if (!(textures[i].img = mlx_xpm_file_to_image(win->mlx, name, \
									&textures[i].width, &textures[i].height)))
			ft_error(data, 8);
		textures[i].data = mlx_get_data_addr(textures[i].img, &textures[i].bpp,\
									&textures[i].linelen, &textures[i].endian);
	}
}
