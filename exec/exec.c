/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:09:10 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/05 21:57:18 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static	double	attenuation_rate(double n_l, t_vectors *eye_scrn, t_vectors *shapeis_lit, t_vectors *shapemid_shapeis)
{
	t_vectors	r_;
	t_vectors	v;

	if (n_l <= 0)
		return (0);
	ready_vector(&r_, 2 * n_l * shapemid_shapeis->unitvect.x - shapeis_lit->unitvect.x, \
	2 * n_l * shapemid_shapeis->unitvect.y - shapeis_lit->unitvect.y,\
	2 * n_l * shapemid_shapeis->unitvect.z - shapeis_lit->unitvect.z);
	ready_vector(&v, -(eye_scrn->vect.x), -(eye_scrn->vect.y), -(eye_scrn->vect.z));
	return (map(vectorinpuro(&(r_.unitvect), &(v.unitvect)), -1, 1, 0, 1));
}

static	double	shade_draw(t_data *info, t_vectors *eye_scrn, t_vectors *eye_shapemid, double r)
{
	t_vectors   shapemid_shapeis;
    t_vectors   o_shapeis;
    t_vectors   shapeis_lit;
	double		n_l;

	scal_vecsum(&o_shapeis, &(info->fixedpoint_vec.parse_vec->vect), &(eye_scrn->vect), intersection_on_circle(&(eye_scrn->vect), &(eye_shapemid->vect), r));
	vectorminus(&shapeis_lit, &(info->fixedpoint_vec.lightsource->vect), &(o_shapeis.vect));
	vectorminus(&shapemid_shapeis, &(o_shapeis.vect), &(info->fixedpoint_vec.shape_midvec->vect));
	n_l = map(vectorinpuro(&(shapemid_shapeis.unitvect), &(shapeis_lit.unitvect)), -1, 1, 0, 1);
	return (pow(attenuation_rate(map(n_l, -1, 1, 0, 1), eye_scrn, &shapeis_lit, &shapemid_shapeis), info->lsinf.alpha) * info->lsinf.ks * info->lsinf.Ii + info->lsinf.kd * info->lsinf.Ii * n_l);
}

void    exec(t_data *info, int x_start, int y_start)
{
    t_vectors	eye_scrn;
    t_vectors   eye_shapemid;
	double    	r = 1;

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			dim_to_tdim(info->fixedpoint_vec.onepointvec, x_start, y_start, (int)info->screenwidth, (int)info->screenheight);
			vectorminus(&eye_scrn, &(info->fixedpoint_vec.onepointvec->vect), &(info->fixedpoint_vec.parse_vec->vect));
			vectorminus(&eye_shapemid, &(info->fixedpoint_vec.parse_vec->vect), &(info->fixedpoint_vec.shape_midvec->vect));
			if (d_coeffi(&(eye_scrn.vect), &(eye_shapemid.vect), r) >= 0)
				draw_fadecolor(info->lsinf.ka * info->lsinf.Ia + shade_draw(info, &eye_scrn, &eye_shapemid, r), info, x_start, y_start);
			else
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF00FF);
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
	mlx_loop(info->info_fordraw.mlx);
}