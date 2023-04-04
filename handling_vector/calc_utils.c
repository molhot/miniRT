/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:38:49 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/04 11:00:50 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	vector_size(t_vector *vec)
{
	double	sum_pow;

	sum_pow = pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2);
	return (sqrt(sum_pow)); 
}
