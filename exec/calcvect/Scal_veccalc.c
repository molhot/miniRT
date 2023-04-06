/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scal_veccalc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:48:26 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/05 21:58:02 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	scal_vecsum(t_vectors *scal_vecsum, t_vector *no_weight, t_vector *weight, double wgh)
{
	scal_vecsum->vect.x = no_weight->x + wgh * weight->x;
	scal_vecsum->vect.y = no_weight->y + wgh * weight->y;
	scal_vecsum->vect.z = no_weight->z + wgh * weight->z;
	scal_vecsum->size = vector_size(&scal_vecsum->vect);
	unitvect_set(scal_vecsum);
}
