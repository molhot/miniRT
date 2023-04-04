/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:25:30 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/30 15:25:30 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"

typedef	struct s_vector
{
	double	x;
	double	y;
	double	z;
}t_vector;

typedef	struct s_vectors
{
	t_vector	vect;
	t_vector	unitvect;
	double		size;
}t_vectors;

typedef struct s_ambientlight
{
	double radiance;
	double reflection_coefficient;
	double intensity;
} t_ambientlight;

typedef struct s_fixedcevts
{
	t_vectors	*parse_vec;
	t_vectors	*shape_midvec;
	t_vectors	*onepointvec;
	t_vectors	*lightsource;
} t_fixedcevts;

typedef struct s_info_fordraw
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
}t_info_fordraw;

typedef struct	s_data {
	t_fixedcevts	fixedpoint_vec;
	t_info_fordraw	info_fordraw;
	double			screenwidth;
	double			screenheight;
} t_data;

double		constrain(double num, double min, double max);
double		map(double num, double min, double max, double t_min, double t_max);
void		construct(t_data *info);

//exec
void		exec(t_data *info, int x_start, int y_start);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_fadecolor(double i, t_data *data, int x, int y);
double		d_coeffi(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r);
double		intersection_on_circle(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r);

//vectorset
void		ready_vector(t_vectors *vectors, double x, double y, double z);
void		unitvect_set(t_vectors *sub);
t_vectors	*dim_to_tdim(t_vectors *t_dim, double x, double y, double width, double height);

//handlingvector
t_vectors	*vectorsum(t_vector *cont1, t_vector *cont2);
t_vectors	*vectorminus(t_vector *cont1, t_vector *cont2);
double		vectorinpuro(t_vector *cont1, t_vector *cont2);
t_vectors	*vectoroupro(t_vector *cont1, t_vector *cont2);
//calc_utils
double		vector_size(t_vector *vec);

#endif