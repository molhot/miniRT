/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:25:28 by user              #+#    #+#             */
/*   Updated: 2023/04/05 21:37:18 by mochitteiun      ###   ########.fr       */
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

void	construct(t_data *info)
{
	ready_mlx(info);
	ready_vect(info);
	ready_lsinfo(&(info->lsinf));
}