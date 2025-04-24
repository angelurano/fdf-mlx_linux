/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:27:19 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/24 14:55:33 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// in bonus can apply rotation, offset, zoom, etc with the camera struct in t_fdf
void	project_vertex_iso(t_vertex *point)
{
	static float	cos30 = 0;
	static float	sin30 = 0;
	float	x;
	float	y;
	float	z; // zoom apply different to axis z
	float	zoom = 10.0f; // zoom is an external var

	if (cos30 == 0 || sin30 == 0)
	{
		cos30 = cos(M_PI / 6);
		sin30 = sin(M_PI / 6);
	}
	x = point->coord.x * zoom;
	y = point->coord.y * zoom;
	z = point->coord.z * zoom * 0.15f;
	point->screen.x = - ((x - y) * cos30) + (WIDTH / 2.0f);
	point->screen.y = ((x + y) * sin30 - z) + (HEIGHT / 2.0f);
}
