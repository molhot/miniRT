/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:09:10 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/04 23:07:26 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->info_fordraw.addr + (y * data->info_fordraw.line_length + x * (data->info_fordraw.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

void	ready_pointvector(t_vector *point, double x, double y, int WIDTH, int HEIGHT)
{
	point->x = (2 * x / (WIDTH - 1)) - 1;
	point->y = (-2 * y / (HEIGHT - 1)) + 1;
	point->z = 0;
}

void    exec(t_data *info, int x_start, int y_start)
{
    t_vectors	*eye_scrn;
    t_vectors   *eye_shapemid;
    t_vectors   *shapemid_shapeis;
    t_vectors    o_shapeis;
    t_vectors    *shapeis_lit;
    t_vector		*parsevect;
    double    l_n_inpro;
    double    r = 1;
    double    t;

	parsevect = &(info->fixedpoint_vec.parse_vec->vect);
    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			dim_to_tdim(info->fixedpoint_vec.onepointvec, x_start, y_start, (int)info->screenwidth, (int)info->screenheight);
			eye_scrn = vectorminus(&(info->fixedpoint_vec.onepointvec->vect), &(info->fixedpoint_vec.parse_vec->vect));
			eye_shapemid = vectorminus(&(info->fixedpoint_vec.parse_vec->vect), &(info->fixedpoint_vec.shape_midvec->vect));
			if (d_coeffi(&(eye_scrn->vect), &(eye_shapemid->vect), r) >= 0)
            {
                t = intersection_on_circle(&(eye_scrn->vect), &(eye_shapemid->vect), r);
                ready_vector(&o_shapeis, parsevect->x + (eye_scrn->vect.x * t), parsevect->y + (eye_scrn->vect.y * t), parsevect->z + (eye_scrn->vect.z * t));
                shapeis_lit = vectorminus(&(info->fixedpoint_vec.lightsource->vect), &(o_shapeis.vect));
                shapemid_shapeis = vectorminus(&(o_shapeis.vect), &(info->fixedpoint_vec.shape_midvec->vect));
                l_n_inpro = map(vectorinpuro(&(shapemid_shapeis->unitvect), &(shapeis_lit->unitvect)), -1, 1, 0, 1);
                my_mlx_pixel_put(info, x_start, y_start, ((int)(255 * l_n_inpro) << 16) | ((int)(255 * l_n_inpro) << 8) | (int)(255 * l_n_inpro));
                free(shapeis_lit);
                free(shapemid_shapeis);
            }
			else
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF00FF);
            free(eye_scrn);
            free(eye_shapemid);
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
	mlx_loop(info->info_fordraw.mlx);
}