/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:27:19 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 03:36:46 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// in bonus can apply rotation, offset, zoom, etc with the camera struct in t_fdf
t_vec2	project_iso(t_vec3 point)
{
	static float	cos30 = 0;
	static float	sin30 = 0;
	t_vec2			iso;

	if (cos30 == 0 || sin30 == 0)
	{
		cos30 = cosf(M_PI / 6);
		sin30 = sinf(M_PI / 6);
	}
	iso.x = -(-point.x - point.y) * cos30;
	iso.y = (-point.x + point.y) * sin30 - point.z;
	return (iso);
}

t_vec2	project_screen(t_zoom zoom, t_vec2 iso)
{
	iso.x = iso.x * zoom.value + zoom.offset.x;
	iso.y = iso.y * zoom.value + zoom.offset.y;
	return (iso);
}

void	apply_transform(t_fdf *fdf)
{
	size_t		i;
	t_vertex	*v;

	i = 0;
	while (i < fdf->points.lines * fdf->points.line_length)
	{
		v = ft_dynarrget(fdf->points.buffer, i);
		v->screen = project_screen(fdf->zoom, v->iso);
		i++;
	}
}

/*
void	project_all_iso(t_fdf *fdf)
{
	size_t		i;
	t_vertex	*v;

	i = 0;
	while (i < fdf->points.lines * fdf->points.line_length)
	{
		v = ft_dynarrget(fdf->points.buffer, i);
		v->iso = project_iso(v->coord);
		v->screen = project_screen(fdf->zoom, v->iso);
		i++;
	}
}

void	project_vertex_iso(t_vertex *point)
{
	float	x;
	float	y;
	float	z; // zoom apply different to axis z
	float	zoom = 1.0f; // zoom is an external var

	if (cos30 == 0 || sin30 == 0)
	{
		cos30 = cos(M_PI / 6);
		sin30 = sin(M_PI / 6);
	}
	x = point->coord.x * zoom;
	y = point->coord.y * zoom;
	z = point->coord.z * zoom;
	point->screen.x = - ((x - y) * cos30) + (WIDTH / 2.0f);
	point->screen.y = ((x + y) * sin30 - z) + (HEIGHT / 2.0f);
}
*/
