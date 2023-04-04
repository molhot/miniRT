/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:35:13 by user              #+#    #+#             */
/*   Updated: 2023/04/04 23:13:28 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ready_vector(t_vectors *vectors, double x, double y, double z)
{
	vectors->vect.x = x;
	vectors->vect.y = y;
	vectors->vect.z = z;
	vectors->size = vector_size(&vectors->vect);
	unitvect_set(vectors);
}

void	unitvect_set(t_vectors *sub)
{
	sub->unitvect.x = sub->vect.x / sub->size;
	sub->unitvect.y = sub->vect.y / sub->size;
	sub->unitvect.z = sub->vect.z / sub->size;
}

t_vectors *dim_to_tdim(t_vectors *t_dim, double x, double y, double width, double height)
{
	t_dim->vect.x = (2 * x / (width - 1)) - 1;
	t_dim->vect.y = (-2 * y / (height - 1)) + 1;
	t_dim->vect.z = 0;
	t_dim->size = vector_size(&t_dim->vect);
	unitvect_set(t_dim);
	return (t_dim);
}
