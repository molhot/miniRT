/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:21:56 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/06 06:37:49 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	typech(t_shapelist list)
{
	if (list.cone != NULL)
		return (CORN);
	if (list.plane != NULL)
		return (PLANE);
	if (list.sphere != NULL)
		return (CIRCLE);
	return (0);
}
