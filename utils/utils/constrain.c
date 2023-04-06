/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constrain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:54:48 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/01 00:02:09 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	constrain(int num, int min, int max)
{
	if (min > num)
		return (min);
	else if (min <= num && num <= max)
		return (num);
	else
		return (max);
}

int map(int num, int min, int max, int t_min, int t_max)
{
	int	constrain_num;

	constrain_num = constrain(num, min, max);
	return (t_min + (t_max - t_min) * constrain_num / (max - min));
}
