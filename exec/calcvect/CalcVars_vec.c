/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CalcVars_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:20 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/04 23:22:35 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_vectors	*vectorsum(t_vector *cont1, t_vector *cont2)
{
	t_vectors	*sum_vectors;

	sum_vectors = malloc(sizeof(t_vectors) * 1);
	sum_vectors->vect.x = cont1->x + cont2->x;
	sum_vectors->vect.y = cont1->y + cont2->y;
	sum_vectors->vect.z = cont1->z + cont2->z;
	sum_vectors->size = vector_size(&sum_vectors->vect);
	unitvect_set(sum_vectors);
	return (sum_vectors);
}

t_vectors	*vectorminus(t_vector *cont1, t_vector *cont2)
{
	t_vectors	*minus_vectors;

	minus_vectors = malloc(sizeof(t_vectors) * 1);
	minus_vectors->vect.x = cont1->x - cont2->x;
	minus_vectors->vect.y = cont1->y - cont2->y;
	minus_vectors->vect.z = cont1->z - cont2->z;
	minus_vectors->size = vector_size(&minus_vectors->vect);
	unitvect_set(minus_vectors);
	return (minus_vectors);
}

double	vectorinpuro(t_vector *cont1, t_vector *cont2)
{
	return (cont1->x * cont2->x + cont1->y * cont2->y + cont1->z * cont2->z);
}

t_vectors	*vectoroupro(t_vector *cont1, t_vector *cont2)
{
	t_vectors	*ouprovector;

	ouprovector = malloc(sizeof(t_vectors) * 1);
	ouprovector->vect.x = cont1->x - cont2->x;
	ouprovector->vect.y = cont1->y - cont2->y;
	ouprovector->vect.z = cont1->z - cont2->z;
	ouprovector->size = vector_size(&ouprovector->vect);
	unitvect_set(ouprovector);
	return (ouprovector);
}
