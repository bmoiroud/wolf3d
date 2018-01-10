/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 13:58:29 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/05/03 14:57:11 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_starting_point(t_data *data, char *line, int *x, int y)
{
	if (data->wolf.pos.x != -1 || data->wolf.pos.y != -1)
		ft_error(data, 6);
	else if (line[*x + 1] == '\0' || y == data->wolf.height || y == 1)
		ft_error(data, 2);
	else
	{
		data->wolf.pos.x = (*x / 2) * WALL_W + WALL_W / 2;
		data->wolf.pos.y = (y - 1) * WALL_W + WALL_W / 2;
		if (line[*x + 1] == ',')
		{
			if (line[*x + 2] == 'N')
				data->wolf.orientation = 360;
			else if (line[*x + 2] == 'E')
				data->wolf.orientation = 90 + 360;
			else if (line[*x + 2] == 'S')
				data->wolf.orientation = 180 + 360;
			else if (line[*x + 2] == 'W')
				data->wolf.orientation = 270 + 360;
			else
				ft_error(data, 2);
			*x += 2;
		}
		else
			data->wolf.orientation = 360;
	}
}

int		ft_check_line(char *line, t_data *data, int y)
{
	int		s;
	int		i;

	i = 1;
	s = 0;
	if (line[0] == 48)
		return (1);
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] == '\0')
			return (1);
		else if (line[i] == ' ')
			s++;
		else if (line[i] == 's')
			ft_starting_point(data, line, &i, y);
		else if (line[i] == 48 && line[i - 1] == ' ' && (line[i + 1] == '\0' \
								|| i == 0 || y == data->wolf.height || y == 1))
			return (1);
		else if ((line[i] > 57 || line[i] < 48) && line[i] != 32 && line[i] != \
																		'\n')
			return (1);
		i++;
	}
	free(line);
	return (data->wolf.width - (s + 1));
}

int		ft_valid_map(t_data *data, t_wolf *wolf, char *file)
{
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(data, 1);
	if ((get_next_line(fd, &line)) == -1)
		ft_error(data, 1);
	if (!(wolf->size = ft_strsplit(line, ' ')))
		ft_error(data, 3);
	if (!wolf->size[0])
		ft_error(data, 2);
	free(line);
	if ((wolf->width = ft_atoi(wolf->size[0])) <= 0 || \
								(wolf->height = ft_atoi(wolf->size[1])) <= 0)
		return (1);
	free(wolf->size[0]);
	free(wolf->size[1]);
	while (get_next_line(fd, &line) && ++i)
		if (ft_check_line(line, data, i) != 0)
			return (1);
	close(fd);
	return (wolf->height - i);
}

int		*ft_filltab(t_data *data, int *dst, char *src)
{
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (!(tab = ft_strsplit(src, ' ')))
		ft_error(data, 3);
	while (tab[++i])
	{
		if (tab[i][0] == 's')
			dst[i] = 0;
		else
			dst[i] = ft_atoi(tab[i]);
		if (dst[i] > NB_TEXTURES || dst[i] < 0)
			ft_error(data, 9);
	}
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (dst);
}

void	ft_getmap(t_data *data, t_wolf *wolf, char *file)
{
	int		i;
	int		fd;
	char	*line;

	line = NULL;
	fd = 0;
	i = 0;
	if (ft_valid_map(data, wolf, file) != 0)
		ft_error(data, 2);
	if ((wolf->map = (int **)malloc(wolf->height * sizeof(int *))) == NULL)
		ft_error(data, 3);
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	free(line);
	while (get_next_line(fd, &line) != 0 && ++i)
	{
		if (!(wolf->map[i - 1] = (int *)malloc(wolf->width * sizeof(int))))
			ft_error(data, 3);
		if (!(wolf->map[i - 1] = ft_filltab(data, wolf->map[i - 1], line)))
			ft_error(data, 3);
		free(line);
	}
	if (wolf->pos.x == -1 || wolf->pos.y == -1)
		ft_error(data, 2);
	close(fd);
}
