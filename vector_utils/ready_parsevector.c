/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_parsevector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:35:13 by user              #+#    #+#             */
/*   Updated: 2023/04/02 14:18:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void    ready_persevector(t_vector *vector, double x, double y, double z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}