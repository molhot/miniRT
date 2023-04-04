/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:09:10 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/05 00:14:56 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static	double	shade_draw(t_data *info, t_vectors *eye_scrn, t_vectors *eye_shapemid, double r)
{
	t_vectors   *shapemid_shapeis;
    t_vectors   o_shapeis;
    t_vectors   *shapeis_lit;
    t_vector	*parsevect;
	double		ans;
    double    	t;

	parsevect = &(info->fixedpoint_vec.parse_vec->vect);
	t = intersection_on_circle(&(eye_scrn->vect), &(eye_shapemid->vect), r);
	ready_vector(&o_shapeis, parsevect->x + (eye_scrn->vect.x * t), parsevect->y + (eye_scrn->vect.y * t), parsevect->z + (eye_scrn->vect.z * t));
	shapeis_lit = vectorminus(&(info->fixedpoint_vec.lightsource->vect), &(o_shapeis.vect));
	shapemid_shapeis = vectorminus(&(o_shapeis.vect), &(info->fixedpoint_vec.shape_midvec->vect));
	ans = map(vectorinpuro(&(shapemid_shapeis->unitvect), &(shapeis_lit->unitvect)), -1, 1, 0, 1);
	free(shapeis_lit);
	free(shapemid_shapeis);
	return (ans);
}

void    exec(t_data *info, int x_start, int y_start)
{
    t_vectors	*eye_scrn;
    t_vectors   *eye_shapemid;
	double    	r = 1;

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			dim_to_tdim(info->fixedpoint_vec.onepointvec, x_start, y_start, (int)info->screenwidth, (int)info->screenheight);
			eye_scrn = vectorminus(&(info->fixedpoint_vec.onepointvec->vect), &(info->fixedpoint_vec.parse_vec->vect));
			eye_shapemid = vectorminus(&(info->fixedpoint_vec.parse_vec->vect), &(info->fixedpoint_vec.shape_midvec->vect));
			if (d_coeffi(&(eye_scrn->vect), &(eye_shapemid->vect), r) >= 0)
				draw_fadecolor(shade_draw(info, eye_scrn, eye_shapemid, r), info, x_start, y_start);
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