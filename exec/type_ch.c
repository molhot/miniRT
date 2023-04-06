/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:21:56 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/04/06 19:51:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	typech(t_shapelist list)
{
	if (list.cone != NULL)
		return (CORN);
	else if (list.plane != NULL)
		return (PLANE);
	else if (list.sphere != NULL)
		return (CIRCLE);
	return (0);
}
