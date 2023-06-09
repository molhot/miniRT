/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_its.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:29:30 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/07 07:42:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

double	d_coeffi(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r)
{
	double coefficient_A;
	double coefficient_B;
	double coefficient_C;

	coefficient_A = pow(vector_size(dir_vec), 2);
	coefficient_B = 2 * (dir_vec->x * dir_tomiddlecir->x + dir_vec->y * dir_tomiddlecir->y + dir_vec->z * dir_tomiddlecir->z);
	coefficient_C = pow(vector_size(dir_tomiddlecir), 2) - pow(r, 2);
	return (pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C);
}

double  intersection_on_circle(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r)
{
    double coefficient_A;
	double coefficient_B;
	double coefficient_C;
    double one_ans;
    double two_ans;

	coefficient_A = pow(vector_size(dir_vec), 2);
	coefficient_B = 2 * (dir_vec->x * ((dir_tomiddlecir)->x) + dir_vec->y * (dir_tomiddlecir->y) + dir_vec->z * (dir_tomiddlecir->z));
	coefficient_C = pow(vector_size(dir_tomiddlecir), 2) - pow(r, 2);

    if ((pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C) == 0)
        return (-1 * coefficient_B / (2 * coefficient_A));
    one_ans = (-1 * coefficient_B + sqrt(d_coeffi(dir_vec, dir_tomiddlecir, r))) / (2 * coefficient_A);
    two_ans = (-1 * coefficient_B - sqrt(d_coeffi(dir_vec, dir_tomiddlecir, r))) / (2 * coefficient_A);
    if (one_ans < 0 || two_ans < 0)
    {
        if (one_ans < 0)
            return two_ans;
        else if (two_ans < 0)
            return one_ans;
    }
    if (one_ans >= two_ans)
        return (two_ans);
    else
        return (one_ans);
}

double  intersection_on_plane(t_vector *o_eye, t_vector *o_scr, t_plane *plane)
{
	double      myu;
    t_vectors   eye_scr;
    double      tmp;

    vectorminus(&eye_scr, o_scr, o_eye);
    tmp = vectorinpuro(&(plane->point), &(plane->n)) -  vectorinpuro(o_eye, &(plane->n));
	myu = tmp / (vectorinpuro(&(eye_scr.vect), &(plane->n)));
	return (myu);
}
