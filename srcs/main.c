/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:14:03 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/04/30 19:35:46 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_free_all(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_TEXTURES)
		if (data->wolf.textures[i].width > 0)
			mlx_destroy_image(data->win.mlx, data->wolf.textures[i].img);
	i = -1;
	while (data->wolf.size && ++i && data->wolf.size[i])
		if (data->wolf.size[i])
			free(data->wolf.size[i]);
	if (data->wolf.size)
		free(data->wolf.size);
	if (data->win.img)
		mlx_destroy_image(data->win.mlx, data->win.img);
	if (data->win.win)
		mlx_destroy_window(data->win.mlx, data->win.win);
	if (data->wolf.sky != 0)
		mlx_destroy_image(data->win.mlx, data->wolf.skybox.img);
	close(data->wolf.sky);
}

void	ft_error(t_data *data, int error)
{
	if (error == 0)
		ft_putstr("usage: ./wolf3d \"map\"\n");
	else if (error == 1)
		ft_putstr("error: invalid file\n");
	else if (error == 2)
		ft_putstr("error: invalid map\n");
	else if (error == 3)
		ft_putstr("malloc error\n");
	else if (error == 4)
		ft_putstr("thread creation error\n");
	else if (error == 5)
		ft_putstr("thread error\n");
	else if (error == 6)
		ft_putstr("error: multiple starting point\n");
	else if (error == 7)
		ft_putstr("error: too many arguments\n");
	else if (error == 8)
		ft_putstr("error: missing texture\n");
	else if (error == 9)
		ft_putstr("error: invalid texture in map\n");
	ft_free_all(data);
	exit(EXIT_FAILURE);
}

int		ft_exit(void *param)
{
	t_data *data;

	data = (t_data *)param;
	mlx_clear_window(data->win.mlx, data->win.win);
	ft_free_all(data);
	exit(EXIT_SUCCESS);
}

void	ft_refresh(t_data *data)
{
	ft_init_threads(data, &data->wolf);
	mlx_put_image_to_window(data->win.mlx, data->win.win, data->win.img, 0, 0);
}

int		main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac < 2)
		ft_error(&data, 0);
	if (ac > 3)
		ft_error(&data, 7);
	if (av[1] == NULL)
		ft_error(&data, 1);
	ft_init_data(&data);
	ft_getmap(&data, &data.wolf, av[1]);
	ft_get_textures(&data, &data.win, data.wolf.textures);
	data.wolf.skypos.x = (data.wolf.width - 1) / 2 * WALL_W;
	data.wolf.skypos.y = (data.wolf.height - 1) / 2 * WALL_W;
	ft_init_threads(&data, &data.wolf);
	mlx_put_image_to_window(data.win.mlx, data.win.win, data.win.img, 0, 0);
	mlx_hook(data.win.win, 2, 3, ft_keyhook, (void *)&data);
	mlx_hook(data.win.win, 17, (1L << 17), ft_exit, (void *)&data);
	mlx_loop(data.win.mlx);
	return (0);
}
