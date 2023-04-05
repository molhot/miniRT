/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:25:28 by user              #+#    #+#             */
/*   Updated: 2023/04/06 07:53:03 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ready_mlx(t_data *info)
{
	info->screenheight = 500;
	info->screenwidth = 500;
	info->info_fordraw.mlx = mlx_init();
	info->info_fordraw.mlx_win = mlx_new_window(info->info_fordraw.mlx, info->screenwidth, info->screenheight, "Hello world!");
	info->info_fordraw.img = mlx_new_image(info->info_fordraw.mlx, info->screenwidth, info->screenheight);
	info->info_fordraw.addr = mlx_get_data_addr(info->info_fordraw.img, &info->info_fordraw.bits_per_pixel, &info->info_fordraw.line_length,&info->info_fordraw.endian);
}

static  void    ready_vect(t_data *info)
{
	info->fixedpoint_vec.parse_vec = malloc(sizeof(t_vectors) * 1);
	info->fixedpoint_vec.onepointvec = malloc(sizeof(t_vectors) * 1);
	info->fixedpoint_vec.shape_midvec = malloc(sizeof(t_vectors) * 1);
	info->fixedpoint_vec.lightsource = malloc(sizeof(t_vectors) * 1);
	ready_vector(info->fixedpoint_vec.parse_vec, 0, 0, -5);
	ready_vector(info->fixedpoint_vec.shape_midvec, 0, 0, 5);
	ready_vector(info->fixedpoint_vec.lightsource, -5, 5, -5);
}

static	void	ready_lsinfo(t_light_source *info)
{
	info->ka = 0.01;
	info->kd = 0.69;
	info->ks = 0.3;
	info->alpha = 8;
	info->Ia = 0.1;
	info->Ii = 1.0;
}

static	void	ready_shapelists(t_data *info)
{
	info->shape_lists = malloc(sizeof(t_shapelists) * 1);
	//本当はここで元となるファイルをもとにワイルをかける
	info->shape_lists->list.sphere = malloc(sizeof(t_sphere) * 1);
	info->shape_lists->list.plane = NULL;
	info->shape_lists->list.cone = NULL;
	ready_vector(&(info->shape_lists->list.sphere->sphere_vec), 0, 0, 5);
	info->shape_lists->list.sphere->r = 1;

	info->shape_lists->next = malloc(sizeof(t_shapelists) * 1);
	info->shape_lists->next->list.sphere = malloc(sizeof(t_sphere) * 1);
	info->shape_lists->next->list.plane = NULL;
	info->shape_lists->next->list.cone = NULL;
	ready_vector(&(info->shape_lists->next->list.sphere->sphere_vec), 1, 0, 1);
	info->shape_lists->next->list.sphere->r = 1;

	info->shape_lists->next->next = malloc(sizeof(t_shapelists) * 1);
	info->shape_lists->next->next->list.plane = malloc(sizeof(t_plane) * 1);
	info->shape_lists->next->next->list.sphere = NULL;
	info->shape_lists->next->next->list.cone = NULL;
	ready_only_vector(&(info->shape_lists->next->next->list.plane->n), 0, 1, 0);
	ready_only_vector(&(info->shape_lists->next->next->list.plane->point), 0, -1, 0);
	t_plane *plane;
	plane = info->shape_lists->next->next->list.plane;
	info->shape_lists->next->next->list.plane->k = vectorinpuro(&(plane->n), &(plane->point));
	info->shape_lists->next->next->next = NULL;
}

static	void	ready_lightsources(t_data *info)
{
	t_light_sources	*lsinfs;

	info->lsinfs = malloc(sizeof(t_light_sources) * 1);
	lsinfs = info->lsinfs;
	lsinfs->lsi = malloc(sizeof(t_vectors) * 1);
	ready_vector(lsinfs->lsi, -5, 5, -5);
	lsinfs->next = malloc(sizeof(t_light_sources) * 1);
	lsinfs = info->lsinfs->next;
	lsinfs->lsi = malloc(sizeof(t_vectors) * 1);
	ready_vector(lsinfs->lsi, 5, 10, -5);
}

void	construct(t_data *info)
{
	ready_mlx(info);
	ready_vect(info);
	ready_lsinfo(&(info->lsinf));
	ready_shapelists(info);
	ready_lightsources(info);
}