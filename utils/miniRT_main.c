/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:36:46 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/02 14:17:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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

int main()
{
	int			WIDTH = 500;
	int 		HEIGHT = 500;
	t_vector	*eye_vect;
	t_vector	*eye_tomidllecircle;
	t_data 		game_all_info;
	t_vector	dir_dim_vec;

	double x_start;
	double y_start;
	double r = 1;

	x_start = 0;
	y_start = 0;
	game_all_info.mlx = mlx_init();
	game_all_info.mlx_win = mlx_new_window(game_all_info.mlx, 500, 500, "Hello world!");
	game_all_info.img = mlx_new_image(game_all_info.mlx, 500, 500);
	game_all_info.addr = mlx_get_data_addr(game_all_info.img, &game_all_info.bits_per_pixel, &game_all_info.line_length,&game_all_info.endian);
	game_all_info.fixedpoint_vec.parse_vec = malloc(sizeof(t_vector) * 1);
	game_all_info.fixedpoint_vec.onepointvec = malloc(sizeof(t_vector) * 1);
	game_all_info.fixedpoint_vec.shape_midvec = malloc(sizeof(t_vector) * 1);
	ready_persevector(game_all_info.fixedpoint_vec.parse_vec, 0, 0, -5);
	ready_persevector(game_all_info.fixedpoint_vec.shape_midvec, 0, 0, 5);
	while (y_start != HEIGHT)
	{
		while (x_start != WIDTH)
		{
			ready_pointvector(game_all_info.fixedpoint_vec.onepointvec, x_start, y_start, WIDTH, HEIGHT);
			eye_vect = vectorminus_dim(game_all_info.fixedpoint_vec.onepointvec, game_all_info.fixedpoint_vec.parse_vec);
			eye_tomidllecircle = vectorminus_dim(game_all_info.fixedpoint_vec.shape_midvec, game_all_info.fixedpoint_vec.parse_vec);
			dir_dim_vec.x = eye_vect->x / vector_size(eye_vect);
			dir_dim_vec.y = eye_vect->y / vector_size(eye_vect);
			dir_dim_vec.z = eye_vect->z / vector_size(eye_vect);
			if (square_root(&dir_dim_vec, eye_tomidllecircle, r) >= 0)
				my_mlx_pixel_put(&game_all_info, x_start, y_start, 0x00FF0000);
			else
				my_mlx_pixel_put(&game_all_info, x_start, y_start, 0x00FF00FF);
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(game_all_info.mlx, game_all_info.mlx_win, game_all_info.img, 0, 0);
	mlx_loop(game_all_info.mlx);
}