/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:09:10 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/06 07:45:02 by mochitteiun      ###   ########.fr       */
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
	t_vectors		shapemid_shapeis;
    t_vectors		o_shapeis;
    t_vectors		shapeis_lit;
	t_light_sources	*lsi_p;
	double			n_l;
	double			RsRd;

	RsRd = 0;
	scal_vecsum(&o_shapeis, &(info->fixedpoint_vec.parse_vec->vect), &(eye_scrn->vect), intersection_on_circle(&(eye_scrn->vect), &(eye_shapemid->vect), r));
	//ここから光源の個数分だけ繰り返し
	lsi_p = info->lsinfs;
	while (lsi_p != NULL)
	{
		vectorminus(&shapeis_lit, &(lsi_p->lsi->vect), &(o_shapeis.vect));
		vectorminus(&shapemid_shapeis, &(o_shapeis.vect), &(info->fixedpoint_vec.shape_midvec->vect));//おかしいかも
		n_l = n_l + map(vectorinpuro(&(shapemid_shapeis.unitvect), &(shapeis_lit.unitvect)), -1, 1, 0, 1);
		RsRd = RsRd + pow(attenuation_rate(map(n_l, -1, 1, 0, 1), eye_scrn, &shapeis_lit, &shapemid_shapeis), info->lsinf.alpha) * info->lsinf.ks * info->lsinf.Ii + info->lsinf.kd * info->lsinf.Ii * n_l;
		lsi_p = lsi_p->next;
	}
	//足したものをリターン
	return (RsRd);
}

static	double	draw_color_plane(t_data *info, t_vectors *eye_scrn, t_plane *plane)
{
    t_vectors		o_shapeits;
    t_vectors		shapeis_lit;
	t_light_sources	*lsi_p;
	double			n_l;
	double			RsRd;

	RsRd = 0;
	scal_vecsum(&o_shapeits, &(info->fixedpoint_vec.parse_vec->vect), &(eye_scrn->vect), intersection_on_plane(&(info->fixedpoint_vec.parse_vec->vect), &(info->fixedpoint_vec.onepointvec->vect), plane));
	lsi_p = info->lsinfs;
	while (lsi_p != NULL)
	{
		vectorminus(&shapeis_lit, &(lsi_p->lsi->vect), &(o_shapeits.vect));
		n_l = n_l + map(vectorinpuro(&(plane->n), &(shapeis_lit.unitvect)), -1, 1, 0, 1);
		RsRd = RsRd + pow(1, info->lsinf.alpha) * info->lsinf.ks * info->lsinf.Ii + info->lsinf.kd * info->lsinf.Ii * n_l;
		lsi_p = lsi_p->next;
	}
	return (RsRd);
}

void    exec(t_data *info, int x_start, int y_start)
{
    t_vectors		eye_scrn;
    t_vectors   	eye_shapemid;
	t_vectors		nearest_sphere;
	t_shapelists	*lists;
	double			distance_row;
	double			tmp_disrow;
	size_t			list_p;
	ssize_t			show_sphe;

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			list_p = 0;
			show_sphe = -1;
			distance_row = 2;
			lists = info->shape_lists;
			dim_to_tdim(info->fixedpoint_vec.onepointvec, x_start, y_start, (int)info->screenwidth, (int)info->screenheight);
			vectorminus(&eye_scrn, &(info->fixedpoint_vec.onepointvec->vect), &(info->fixedpoint_vec.parse_vec->vect));
			//各物体ごとに繰り返し計算すべき箇所 最後まで繰り返すべき 物体によって計算方法が変わる
			while (lists != NULL)
			{
				if (typech(lists->list) == CIRCLE)
				{
					vectorminus(&eye_shapemid, &(info->fixedpoint_vec.parse_vec->vect), &(lists->list.sphere->sphere_vec.vect));
					if (d_coeffi(&(eye_scrn.vect), &(eye_shapemid.vect), lists->list.sphere->r) >= 0)
					{
						tmp_disrow = intersection_on_circle(&(eye_scrn.vect), &(eye_shapemid.vect), lists->list.sphere->r);
						if (distance_row > tmp_disrow)
						{
							nearest_sphere = eye_shapemid;
							distance_row = tmp_disrow;
							show_sphe = list_p;
						}
					}
				}
				else if (typech(lists->list) == PLANE)
				{
					if (vectorinpuro(&eye_scrn.vect, &(lists->list.plane->n)) != 0)
					{
						tmp_disrow = intersection_on_plane(&(info->fixedpoint_vec.parse_vec->vect), &(info->fixedpoint_vec.onepointvec->vect), lists->list.plane);
						if (tmp_disrow != 0 && tmp_disrow > distance_row)
						{
							distance_row = tmp_disrow;
							show_sphe = list_p;
						}
					}
				}
				list_p++;
				lists = lists->next;
			}
			//ここまで
			lists = info->shape_lists;
			if (show_sphe == -1)
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF00FF);
			else
			{
				while (show_sphe != 0)
				{
					lists = lists->next;
					show_sphe--;
				}
				if (typech(lists->list) == CIRCLE)
					draw_fadecolor(info->lsinf.ka * info->lsinf.Ia + shade_draw(info, &eye_scrn, &nearest_sphere, lists->list.sphere->r), info, x_start, y_start);
				else if (typech(lists->list) == PLANE)
					draw_fadecolor(info->lsinf.ka * info->lsinf.Ia + draw_color_plane(info, &eye_scrn, lists->list.plane), info, x_start, y_start);
			}
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(info->info_fordraw.mlx, info->info_fordraw.mlx_win, info->info_fordraw.img, 0, 0);
	mlx_loop(info->info_fordraw.mlx);
}