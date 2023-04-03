/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:38:33 by user              #+#    #+#             */
/*   Updated: 2023/04/03 16:26:04 by mochitteiun      ###   ########.fr       */
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
    t_vector	*eye_scrn;
	t_vector	*eye_tomidllecircle;
    t_vector	*dir_dim_vec;
    t_vector    *before_intersection;
    t_vector    *intersection_vect_dummy;
    t_vector    *light_to_oncircle_;
    t_vector    *light_to_oncircle_unitvec;
    t_vector    *lastvec;
    t_vector    *parsevect;
    double      l_n_inpro;
    double      size;

    double      r = 1;
    size_t      i = 0;
    double      t;

    //intersection_vect = malloc(sizeof(t_vector) * 1);
    light_to_oncircle_unitvec = malloc(sizeof(t_vector) * 1);
    intersection_vect_dummy = malloc(sizeof(t_vector) * 1);
    dir_dim_vec = malloc(sizeof(t_vector) * 1);
    lastvec = malloc(sizeof(t_vector) * 1);

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			ready_pointvector(info->fixedpoint_vec.onepointvec, x_start, y_start, info->screenwidth, info->screenheight);
			eye_scrn = vectorminus_dim(info->fixedpoint_vec.onepointvec, info->fixedpoint_vec.parse_vec);
			eye_tomidllecircle = vectorminus_dim(info->fixedpoint_vec.parse_vec, info->fixedpoint_vec.shape_midvec);
            ready_persevector(dir_dim_vec, eye_scrn->x / vector_size(eye_scrn), eye_scrn->y / vector_size(eye_scrn), eye_scrn->z / vector_size(eye_scrn));
			if (d_coeffi(eye_scrn, eye_tomidllecircle, r) >= 0)
            {
                t = intersection_on_circle(eye_scrn, eye_tomidllecircle, r);
                parsevect = info->fixedpoint_vec.parse_vec;
                ready_persevector(intersection_vect_dummy, parsevect->x + (eye_scrn->x * t), parsevect->y + (eye_scrn->y * t), parsevect->z + (eye_scrn->z * t));
                light_to_oncircle_ = vectorminus_dim(info->fixedpoint_vec.lightsource, intersection_vect_dummy);
                size = vector_size(light_to_oncircle_);
                ready_persevector(light_to_oncircle_unitvec, light_to_oncircle_->x / size, light_to_oncircle_->y / size, light_to_oncircle_->z / size);
                before_intersection = vectorminus_dim(intersection_vect_dummy, info->fixedpoint_vec.shape_midvec);
                size = vector_size(before_intersection);
                ready_persevector(lastvec, before_intersection->x / size, before_intersection->y / size, before_intersection->z / size);
                l_n_inpro = vectorinpuro_dim(lastvec, light_to_oncircle_unitvec);
                if (l_n_inpro > 0)
                    i++;
                l_n_inpro = map(l_n_inpro, -1, 1, 0, 1);
                my_mlx_pixel_put(info, x_start, y_start, ((int)(255 * l_n_inpro) << 16) | ((int)(255 * l_n_inpro) << 8) | (int)(255 * l_n_inpro));
                //my_mlx_pixel_put(info, x_start, y_start, 0xFF0000 * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro);
                free(light_to_oncircle_);
                free(before_intersection);
                free(lastvec);
                lastvec = malloc(sizeof(t_vector) * 1);
            }
			else
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF00FF);
            free(eye_scrn);
            free(eye_tomidllecircle);
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
    printf("%ld\n", i);
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
	mlx_loop(info->info_fordraw.mlx);
}