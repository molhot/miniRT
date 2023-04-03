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

typedef	struct s_unitvect
{
	double	x;
	double	y;
	double	z;
}t_unitvect;

typedef	struct s_vector
{
	double		x;
	double		y;
	double		z;
	double		size;
	t_unitvect	unitvect;
}t_vector;

typedef struct s_ambientlight
{
	double radiance;
	double reflection_coefficient;
	double intensity;
} t_ambientlight;

typedef struct s_vectors
{
	t_vector	*parse_vec;
	t_vector	*shape_midvec;
	t_vector	*onepointvec;
	t_vector	*lightsource;
} t_vectors;

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
	t_vectors		fixedpoint_vec;
	t_info_fordraw	info_fordraw;
	double			screenwidth;
	double			screenheight;
} t_data;

t_vector	*vectorsum_dim(t_vector *cont1, t_vector *cont2);
t_vector	*vectorminus_dim(t_vector *cont1, t_vector *cont2);
double		vectorinpuro_dim(t_vector *cont1, t_vector *cont2);
double		constrain(double num, double min, double max);
double 		map(double num, double min, double max, double t_min, double t_max);
void    	ready_persevector(t_vector *vector, double x, double y, double z);
double		vector_size(t_vector *vec);
void	    construct(t_data *info);
void	    exec(t_data *info, int x_start, int y_start);
void		unitvect_set(t_vector *sub);

#endif