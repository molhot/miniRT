/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:25:28 by user              #+#    #+#             */
/*   Updated: 2023/04/02 17:48:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void    construct(t_data *info)
{
    info->screenheight = 500;
    info->screenwidth = 500;
    info->info_fordraw.mlx = mlx_init();
    info->info_fordraw.mlx_win = mlx_new_window(info->info_fordraw.mlx, info->screenwidth, info->screenheight, "Hello world!");
    info->info_fordraw.img = mlx_new_image(info->info_fordraw.mlx, info->screenwidth, info->screenheight);
    info->info_fordraw.addr = mlx_get_data_addr(info->info_fordraw.img, &info->info_fordraw.bits_per_pixel, &info->info_fordraw.line_length,&info->info_fordraw.endian);
    info->fixedpoint_vec.parse_vec = malloc(sizeof(t_vector) * 1);
	info->fixedpoint_vec.onepointvec = malloc(sizeof(t_vector) * 1);
	info->fixedpoint_vec.shape_midvec = malloc(sizeof(t_vector) * 1);
    info->fixedpoint_vec.lightsource = malloc(sizeof(t_vector) * 1);
    ready_persevector(info->fixedpoint_vec.parse_vec, 0, 0, -5);
	ready_persevector(info->fixedpoint_vec.shape_midvec, 0, 0, 5);
    ready_persevector(info->fixedpoint_vec.lightsource, -5, 5, -5);
}