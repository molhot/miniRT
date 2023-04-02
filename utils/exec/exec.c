/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:38:33 by user              #+#    #+#             */
/*   Updated: 2023/04/02 14:43:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->info_fordraw.addr + (y * data->info_fordraw.line_length + x * (data->info_fordraw.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	square_root(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r)
{
	double coefficient_A;
	double coefficient_B;
	double coefficient_C;

	coefficient_A = pow(vector_size(dir_vec), 2);
	coefficient_B = 2 * (dir_vec->x * dir_tomiddlecir->x + dir_vec->y * dir_tomiddlecir->y + dir_vec->z * dir_tomiddlecir->z);
	coefficient_C = pow(vector_size(dir_tomiddlecir), 2) - pow(r, 2);
	return (pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C);
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

    double      r = 1;

    while (y_start != info->screenheight)
	{
		while (x_start != info->screenwidth)
		{
			ready_pointvector(info->fixedpoint_vec.onepointvec, x_start, y_start, info->screenwidth, info->screenheight);
			eye_vect = vectorminus_dim(info->fixedpoint_vec.onepointvec, info->fixedpoint_vec.parse_vec);
			eye_tomidllecircle = vectorminus_dim(info->fixedpoint_vec.shape_midvec, info->fixedpoint_vec.parse_vec);
			dir_dim_vec.x = eye_vect->x / vector_size(eye_vect);
			dir_dim_vec.y = eye_vect->y / vector_size(eye_vect);
			dir_dim_vec.z = eye_vect->z / vector_size(eye_vect);
			if (square_root(&dir_dim_vec, eye_tomidllecircle, r) >= 0)
				my_mlx_pixel_put(info, x_start, y_start, 0x00FF0000);
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