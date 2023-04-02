/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension_vectorcal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:38:49 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/02 16:34:21 by user             ###   ########.fr       */
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
	t_vector	*sum_vector;

	sum_vector = malloc(sizeof(t_vector) * 1);
	sum_vector->x = cont1->x - cont2->x;
	sum_vector->y = cont1->y - cont2->y;
	sum_vector->z = cont1->z - cont2->z;

	return (sum_vector);
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

/*test
int main()
{
	t_vector	v1;
	t_vector	v2;
	t_vector	*v3;

	(v1.x) = 3;
	(v1.y) = 6;
	(v1.z) = 9;

	(v2.x) = 3;
	(v2.y) = 6;
	(v2.z) = 9;

	v3 = vectorsum_dim(&v1, &v2);
	printf("%d\n", v3->x);
	printf("%d\n", v3->y);
	printf("%d\n", v3->z);
}
*/