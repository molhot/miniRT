/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension_vectorcal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:38:49 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/03 18:42:42 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vector	*vectorsum_dim(t_vector *cont1, t_vector *cont2)
{
	t_vector	*sum_vector;

	sum_vector = malloc(sizeof(t_vector) * 1);
	sum_vector->x = cont1->x + cont2->x;
	sum_vector->y = cont1->y + cont2->y;
	sum_vector->z = cont1->z + cont2->z;

	return (sum_vector);
}

t_vector	*vectorminus_dim(t_vector *cont1, t_vector *cont2)
{
	t_vector	*minus_vector;

	minus_vector = malloc(sizeof(t_vector) * 1);
	minus_vector->x = cont1->x - cont2->x;
	minus_vector->y = cont1->y - cont2->y;
	minus_vector->z = cont1->z - cont2->z;

	return (minus_vector);
}

double	vectorinpuro_dim(t_vector *cont1, t_vector *cont2)
{
	return (cont1->x * cont2->x + cont1->y * cont2->y + cont1->z * cont2->z);
}

t_vector	*vectoroupro_dim(t_vector *cont1, t_vector *cont2)
{
	t_vector	*sum_vector;

	sum_vector = malloc(sizeof(t_vector) * 1);
	sum_vector->x = (cont1->y * cont2->z) - (cont1->z * cont2->y);
	sum_vector->y = (cont1->z * cont2->x) - (cont1->x * cont2->z);
	sum_vector->z = (cont1->x * cont2->y) - (cont1->y * cont2->x);
	return (sum_vector);
}

double	vector_size(t_vector *vec)
{
	double	sum_pow;

	sum_pow = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	return (sqrt(sum_pow)); 
}

void	unitvect_set(t_vector *sub)
{
	sub->size = vector_size(sub);
	sub->unitvect.x = sub->x / sub->size;
	sub->unitvect.y = sub->y / sub->size;
	sub->unitvect.z = sub->z / sub->size;
}
