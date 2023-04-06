/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dim_to_tdim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:04:26 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/01 00:30:04 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vector *dim_to_tdim(int x, int y, int width, int height)
{
	t_vector	*t_dim;

	t_dim = malloc(sizeof(t_vector) * 1);
	t_dim->x = (2 * x / (width - 1)) - 1;
	t_dim->y = (-2 * y / (height - 1)) + 1;
	t_dim->z = 0;
	return (t_dim);
}