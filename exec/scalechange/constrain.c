/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constrain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:54:48 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/05 11:42:45 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

double	constrain(double num, double min, double max)
{
	if (min > num)
		return (min);
	else if (min <= num && num <= max)
		return (num);
	else
		return (max);
}

double map(double num, double min, double max, double t_min, double t_max)
{
	double	constrain_num;
	double	tmp;

	constrain_num = constrain(num, min, max);
	tmp = t_min + (t_max - t_min) * constrain_num / (max - min);
	if (tmp < t_min)
		return (t_min);
	else
		return (tmp);
}
