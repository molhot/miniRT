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

typedef struct s_vectors
{
	t_vector	*parse_vec;
	t_vector	*shape_midvec;
	t_vector	*onepointvec;
} t_vectors;

typedef struct	s_data {
	t_vectors	fixedpoint_vec;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
} t_data;

t_vector	*vectorsum_dim(t_vector *cont1, t_vector *cont2);
t_vector	*vectorminus_dim(t_vector *cont1, t_vector *cont2);
t_vector	*vectorinpuro_dim(t_vector *cont1, t_vector *cont2);
int			constrain(int num, int min, int max);
int			map(int num, int min, int max, int t_min, int t_max);
void    ready_persevector(t_vector *vector, double x, double y, double z);
double		vector_size(t_vector *vec);

#endif