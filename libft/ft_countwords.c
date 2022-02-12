/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:39:47 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/23 13:42:08 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(const char *str, char c)
{
	int nb;

	nb = 0;
	while (*str && ++nb)
	{
		while (*str == c)
			str++;
		if (!*str)
			return (nb);
		else
			str++;
	}
	return (nb);
}
