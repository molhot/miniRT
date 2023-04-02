/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:38:33 by user              #+#    #+#             */
/*   Updated: 2023/04/02 18:04:36 by user             ###   ########.fr       */
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
	coefficient_B = 2 * (dir_vec->x * dir_tomiddlecir->x + dir_vec->y * dir_tomiddlecir->y + dir_vec->z * dir_tomiddlecir->z);
	coefficient_C = pow(vector_size(dir_tomiddlecir), 2) - pow(r, 2);

    if ((pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C) == 0)
        return (-coefficient_B / (2 * coefficient_A));
    one_ans = (-coefficient_B + sqrt(pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C)) / (2 * coefficient_A);
    two_ans = (-coefficient_B - sqrt(pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C)) / (2 * coefficient_A);
    if (one_ans < 0 || two_ans < 0)
    {
        if (one_ans < 0)
            return two_ans;
        else if (two_ans < 0)
            return one_ans;
    }
    if (one_ans > two_ans)
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
    t_vector	*eye_vect;
	t_vector	*eye_tomidllecircle;
    t_vector	dir_dim_vec;
    t_vector    intersection_vect;
    t_vector    light_to_oncircle_unitvec;
    double      l_n_inpro;

    double      r = 1;
    size_t      i = 0;

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			ready_pointvector(info->fixedpoint_vec.onepointvec, x_start, y_start, info->screenwidth, info->screenheight);
			eye_vect = vectorminus_dim(info->fixedpoint_vec.onepointvec, info->fixedpoint_vec.parse_vec);
			eye_tomidllecircle = vectorminus_dim(info->fixedpoint_vec.shape_midvec, info->fixedpoint_vec.parse_vec);
            ready_persevector(&dir_dim_vec, eye_vect->x / vector_size(eye_vect), eye_vect->y / vector_size(eye_vect), eye_vect->z / vector_size(eye_vect));
			if (d_coeffi(&dir_dim_vec, eye_tomidllecircle, r) >= 0)
            {
                ready_persevector(&intersection_vect, info->fixedpoint_vec.parse_vec->x + (dir_dim_vec.x *  intersection_on_circle(&dir_dim_vec, eye_tomidllecircle, r)), info->fixedpoint_vec.parse_vec->y + (dir_dim_vec.y *  intersection_on_circle(&dir_dim_vec, eye_tomidllecircle, r)), info->fixedpoint_vec.parse_vec->z + (dir_dim_vec.z *  intersection_on_circle(&dir_dim_vec, eye_tomidllecircle, r)));
                ready_persevector(&light_to_oncircle_unitvec, (info->fixedpoint_vec.lightsource->x - intersection_vect.x), (info->fixedpoint_vec.lightsource->y - intersection_vect.y), (info->fixedpoint_vec.lightsource->z - intersection_vect.z));
                //printf("%f\n", light_to_oncircle_unitvec.x);
                ready_persevector(&light_to_oncircle_unitvec, light_to_oncircle_unitvec.x / vector_size(&light_to_oncircle_unitvec), light_to_oncircle_unitvec.y / vector_size(&light_to_oncircle_unitvec), light_to_oncircle_unitvec.z / vector_size(&light_to_oncircle_unitvec));
                //printf("%f\n", light_to_oncircle_unitvec.x);
                ready_persevector(&intersection_vect, intersection_vect.x - info->fixedpoint_vec.shape_midvec->x, intersection_vect.y - info->fixedpoint_vec.shape_midvec->y, intersection_vect.z - info->fixedpoint_vec.shape_midvec->z);
                ready_persevector(&intersection_vect, intersection_vect.x / vector_size(&intersection_vect), intersection_vect.y / vector_size(&intersection_vect), intersection_vect.z / vector_size(&intersection_vect));
                l_n_inpro = vectorinpuro_dim(&intersection_vect, &light_to_oncircle_unitvec);
                if (l_n_inpro < 0)
                    l_n_inpro = 0;
                else if (l_n_inpro > 1)
                    l_n_inpro = 1;
                else
                    i++;
				my_mlx_pixel_put(info, x_start, y_start, 0x00FFFFFF * l_n_inpro * l_n_inpro * l_n_inpro);
            }
			else
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF00FF);
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
    printf("%ld\n", i);
	mlx_loop(info->info_fordraw.mlx);
}