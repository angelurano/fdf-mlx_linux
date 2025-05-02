/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:27:19 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/03 01:05:21 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	iso.x = (point.x + point.y) * cos30;
	iso.y = - (point.x - point.y) * sin30 - point.z;
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
	t_vertex	*v;
	size_t		i;

	i = 0;
	v = ft_dynarrget(fdf->points.buffer, 0);
	while (i < fdf->points.buffer->size)
	{
		v[i].screen = project_screen(fdf->zoom, v[i].iso);
		i++;
	}
}
