/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   exec.c            :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2023/04/02 14:38:33 by user           #+#  #+#          */
/*   Updated: 2023/04/03 16:42:22 by mochitteiun      ###   ########.fr    */
/*                                      */
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
    t_vector    *eye_shapemid;
    t_vector    *shapemid_shapeis;
    t_vector    *o_shapeis;
    t_vector    *shapeis_lit;
    t_vector    *shapeis_lit_unitvec;
    t_vector    *shapemid_shapeis_unitvec;
    t_vector    *parsevect;
    double    l_n_inpro;
    double    size;

    double    r = 1;
    size_t    i = 0;
    double    t;

    shapeis_lit_unitvec = malloc(sizeof(t_vector) * 1);
    o_shapeis = malloc(sizeof(t_vector) * 1);
    shapemid_shapeis_unitvec = malloc(sizeof(t_vector) * 1);

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			ready_pointvector(info->fixedpoint_vec.onepointvec, x_start, y_start, info->screenwidth, info->screenheight);
			eye_scrn = vectorminus_dim(info->fixedpoint_vec.onepointvec, info->fixedpoint_vec.parse_vec);
			eye_shapemid = vectorminus_dim(info->fixedpoint_vec.parse_vec, info->fixedpoint_vec.shape_midvec);
			if (d_coeffi(eye_scrn, eye_shapemid, r) >= 0)
            {
                t = intersection_on_circle(eye_scrn, eye_shapemid, r);
                parsevect = info->fixedpoint_vec.parse_vec;
                ready_persevector(o_shapeis, parsevect->x + (eye_scrn->x * t), parsevect->y + (eye_scrn->y * t), parsevect->z + (eye_scrn->z * t));
                shapeis_lit = vectorminus_dim(info->fixedpoint_vec.lightsource, o_shapeis);
                size = vector_size(shapeis_lit);
                ready_persevector(shapeis_lit_unitvec, shapeis_lit->x / size, shapeis_lit->y / size, shapeis_lit->z / size);
                shapemid_shapeis = vectorminus_dim(o_shapeis, info->fixedpoint_vec.shape_midvec);
                size = vector_size(shapemid_shapeis);
                ready_persevector(shapemid_shapeis_unitvec, shapemid_shapeis->x / size, shapemid_shapeis->y / size, shapemid_shapeis->z / size);
                l_n_inpro = vectorinpuro_dim(shapemid_shapeis_unitvec, shapeis_lit_unitvec);
                if (l_n_inpro > 0)
                    i++;
                l_n_inpro = map(l_n_inpro, -1, 1, 0, 1);
                my_mlx_pixel_put(info, x_start, y_start, ((int)(255 * l_n_inpro) << 16) | ((int)(255 * l_n_inpro) << 8) | (int)(255 * l_n_inpro));
                //my_mlx_pixel_put(info, x_start, y_start, 0xFF0000 * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro * l_n_inpro);
                free(shapeis_lit);
                free(shapemid_shapeis);
                free(shapemid_shapeis_unitvec);
                shapemid_shapeis_unitvec = malloc(sizeof(t_vector) * 1);
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
    printf("%ld\n", i);
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
	mlx_loop(info->info_fordraw.mlx);
}