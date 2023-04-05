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

typedef	struct s_cone{

}t_cone;

typedef	struct s_plane{
	t_vector	n;
	t_vector	point;
}t_plane;

typedef	struct s_sphere{
	t_vectors	sphere_vec;
	double		r;
}t_sphere;

typedef	struct s_shapelist{
	t_cone		*cone;
	t_plane		*plane;
	t_sphere	*sphere;
}t_shapelist;

typedef struct s_shapelists t_shapelists;

struct s_shapelists{
	t_shapelist		list;
	t_shapelists	*next;
};

typedef struct s_light_source {
	double	ka;
	double	kd;
	double	ks;
	double	alpha;
	double	Ia;
	double	Ii;
	double	n_l;
	double	v_r;
	double	Rs;
}t_light_source;

typedef struct	s_data {
	t_fixedcevts	fixedpoint_vec;
	t_info_fordraw	info_fordraw;
	t_shapelists	*shape_lists;
	t_light_source	lsinf;
	double			screenwidth;
	double			screenheight;
} t_data;

//construct
void		construct(t_data *info);

//exec
void		exec(t_data *info, int x_start, int y_start);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_fadecolor(double i, t_data *data, int x, int y);
double		d_coeffi(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r);
double		intersection_on_circle(t_vector *dir_vec, t_vector *dir_tomiddlecir, double r);
double		constrain(double num, double min, double max);
double		map(double num, double min, double max, double t_min, double t_max);

//vectorset
void		ready_vector(t_vectors *vectors, double x, double y, double z);
void		unitvect_set(t_vectors *sub);
t_vectors	*dim_to_tdim(t_vectors *t_dim, double x, double y, double width, double height);

//handlingvector
void		vectorsum(t_vectors *sum_vectors, t_vector *cont1, t_vector *cont2);
void		vectorminus(t_vectors *minus_vectors, t_vector *cont1, t_vector *cont2);
double		vectorinpuro(t_vector *cont1, t_vector *cont2);
void		vectoroupro(t_vectors *ouprovector, t_vector *cont1, t_vector *cont2);
void		scal_vecsum(t_vectors *scal_vecsum, t_vector *no_weight, t_vector *weight, double wgh);
//calc_utils
double		vector_size(t_vector *vec);

#endif