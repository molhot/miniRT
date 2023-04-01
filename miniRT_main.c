/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:36:46 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/02 03:09:05 by user             ###   ########.fr       */
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

int main()
{
	int			WIDTH = 500;
	int 		HEIGHT = 500;
	t_vector	*parse_vector;
	t_vector	*ball;
	t_vector	oneppoint;
	t_data 		game_all_info;
	//size_t		color_int;

	// game_all_info.mlx = mlx_init();
	// game_all_info.win = mlx_new_window(game_all_info.mlx, WIDTH, HEIGHT, "test");
	// my_mlx_pixel_put(game_all_info->img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(game_all_info.mlx);
	double x_start;
	double y_start;

	x_start = 0;
	y_start = 0;
	//color_int = 0x00FF0000;
	game_all_info.mlx = mlx_init();
	game_all_info.mlx_win = mlx_new_window(game_all_info.mlx, 500, 500, "Hello world!");
	game_all_info.img = mlx_new_image(game_all_info.mlx, 500, 500);
	game_all_info.addr = mlx_get_data_addr(game_all_info.img, &game_all_info.bits_per_pixel, &game_all_info.line_length,&game_all_info.endian);
	/*特殊ケース*/
	double r = 1;
	parse_vector = malloc(sizeof(t_vector) * 1);
	ball = malloc(sizeof(t_vector) * 1);
	ready_persevector(parse_vector, 0, 0, -5);
	printf("%f\n", parse_vector->z);
	ready_persevector(ball, 0, 0, 5);
	/**/

	t_vector	*eye_vect;
	t_vector	*eye_tomidllecircle;
	while (y_start != HEIGHT)
	{
		while (x_start != WIDTH)
		{
			oneppoint.x = (2 * x_start / (WIDTH - 1)) - 1;
			oneppoint.y = (-2 * y_start / (HEIGHT - 1)) + 1;
			oneppoint.z = 0;
			eye_vect = vectorminus_dim(&oneppoint, parse_vector);
			eye_tomidllecircle = vectorminus_dim(ball, parse_vector);
			double dir_dimention = vector_size(eye_vect);
			t_vector	dir_dim_vec;
			dir_dim_vec.x = eye_vect->x / dir_dimention;
			dir_dim_vec.y = eye_vect->y / dir_dimention;
			dir_dim_vec.z = eye_vect->z / dir_dimention;
			//t倍したeyevectorが円上に存在しているか
			if (square_root(&dir_dim_vec, eye_tomidllecircle, r) >= 0)
			{
				my_mlx_pixel_put(&game_all_info, x_start, y_start, 0x00FF0000);
			}
			else
			{
				//printf("check\n");
				my_mlx_pixel_put(&game_all_info, x_start, y_start, 0x00FF00FF);
			}
			x_start++;
		}
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(game_all_info.mlx, game_all_info.mlx_win, game_all_info.img, 0, 0);
	mlx_loop(game_all_info.mlx);
}