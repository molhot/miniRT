/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:36:46 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/30 23:24:54 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main()
{
	int WIDTH = 500;
	int HEIGHT = 1000;
	t_data game_all_info;
	size_t	color_int;

	// game_all_info.mlx = mlx_init();
	// game_all_info.win = mlx_new_window(game_all_info.mlx, WIDTH, HEIGHT, "test");
	// my_mlx_pixel_put(game_all_info->img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(game_all_info.mlx);
	int x_start;
	int y_start;

	x_start = 0;
	y_start = 0;
	color_int = 0x00FF0000;
	game_all_info.mlx = mlx_init();
	game_all_info.mlx_win = mlx_new_window(game_all_info.mlx, 1920, 1080, "Hello world!");
	game_all_info.img = mlx_new_image(game_all_info.mlx, 1920, 1080);
	game_all_info.addr = mlx_get_data_addr(game_all_info.img, &game_all_info.bits_per_pixel, &game_all_info.line_length,&game_all_info.endian);
	while (y_start != HEIGHT)
	{
		while (x_start != WIDTH)
		{
			my_mlx_pixel_put(&game_all_info, x_start, y_start, color_int);
			x_start++;
			color_int = color_int + 1;
		}
		color_int = 0x00FF0000;
		y_start++;
		x_start = 0;
	}
	mlx_put_image_to_window(game_all_info.mlx, game_all_info.mlx_win, game_all_info.img, 0, 0);
	mlx_loop(game_all_info.mlx);
}