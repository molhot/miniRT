/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CalcVars_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:20 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/05 15:31:48 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	vectorsum(t_vectors *sum_vectors, t_vector *cont1, t_vector *cont2)
{
	sum_vectors->vect.x = cont1->x + cont2->x;
	sum_vectors->vect.y = cont1->y + cont2->y;
	sum_vectors->vect.z = cont1->z + cont2->z;
	sum_vectors->size = vector_size(&sum_vectors->vect);
	unitvect_set(sum_vectors);
}

void	vectorminus(t_vectors *minus_vectors, t_vector *cont1, t_vector *cont2)
{
	minus_vectors->vect.x = cont1->x - cont2->x;
	minus_vectors->vect.y = cont1->y - cont2->y;
	minus_vectors->vect.z = cont1->z - cont2->z;
	minus_vectors->size = vector_size(&minus_vectors->vect);
	unitvect_set(minus_vectors);
}

void	reverse_vect(t_vectors *rev_vect, t_vector *vect)
{
	rev_vect->vect.x = -(vect->x);
	rev_vect->vect.y = -(vect->y);
	rev_vect->vect.z = -(vect->z);
	rev_vect->size = vector_size(&rev_vect->vect);
	unitvect_set(rev_vect);
}

double	vectorinpuro(t_vector *cont1, t_vector *cont2)
{
	return (cont1->x * cont2->x + cont1->y * cont2->y + cont1->z * cont2->z);
}

void	vectoroupro(t_vectors *ouprovector, t_vector *cont1, t_vector *cont2)
{
	ouprovector->vect.x = cont1->x - cont2->x;
	ouprovector->vect.y = cont1->y - cont2->y;
	ouprovector->vect.z = cont1->z - cont2->z;
	ouprovector->size = vector_size(&ouprovector->vect);
	unitvect_set(ouprovector);
}
