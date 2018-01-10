/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:16:23 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/04/30 16:27:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		ft_keyhook(int key, void *param)
{
	if (key == 53)
		ft_exit(param);
	else if (key == 126 || key == 13)
		ft_move((t_data *)param, -1);
	else if (key == 125 || key == 1)
		ft_move((t_data *)param, 1);
	else if (key == 124 || key == 123)
		ft_rotate((t_data *)param, key);
	return (0);
}
