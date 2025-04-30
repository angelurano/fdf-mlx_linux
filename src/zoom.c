/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:29:57 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/30 16:24:40 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_mins_maxs(t_fdf *fdf, t_vec2 *min, t_vec2 *max)
{
	t_vertex	*v;
	size_t		i;

	min->x = FLT_MAX;
	min->y = FLT_MAX;
	max->x = -FLT_MAX;
	max->y = -FLT_MAX;
	i = 0;
	while (i < fdf->points.lines * fdf->points.line_length)
	{
		v = ft_dynarrget(fdf->points.buffer, i);
		v->iso = project_iso(v->coord);
		if (v->iso.x < min->x)
			min->x = v->iso.x;
		if (v->iso.y < min->y)
			min->y = v->iso.y;
		if (v->iso.x > max->x)
			max->x = v->iso.x;
		if (v->iso.y > max->y)
			max->y = v->iso.y;
		i++;
	}
}

void	init_zoom(t_fdf *fdf)
{
	t_vec2		min;
	t_vec2		max;
	float		w;
	float		h;
	t_vec2		center;

	get_mins_maxs(fdf, &min, &max);
	w = max.x - min.x;
	if (w <= 0)
		w = 1;
	h = max.y - min.y;
	if (h <= 0)
		h = 1;
	fdf->zoom.value = fminf((float)WIDTH / w, (float)HEIGHT / h) * 0.95f;
	center.x = (max.x + min.x) * 0.5f * fdf->zoom.value;
	center.y = (max.y + min.y) * 0.5f * fdf->zoom.value;
	fdf->zoom.offset.x = (WIDTH / 2.0f) - center.x;
	fdf->zoom.offset.y = (HEIGHT / 2.0f) - center.y;
	fdf->zoom.factor = 1.05f;
}

void	zoom_center(t_fdf *fdf, float new_zoom)
{
	t_zoom	*zoom;
	float	cx;
	float	cy;

	if (new_zoom < 0.1f)
		new_zoom = 0.1f;
	else if (new_zoom > 100.0f)
		new_zoom = 100.0f;
	zoom = &fdf->zoom;
	if (zoom->value == new_zoom)
		return ;
	cx = (float)WIDTH / 2.0f;
	cy = (float)HEIGHT / 2.0f;
	zoom->offset.x = cx + (zoom->offset.x - cx) * (new_zoom / zoom->value);
	zoom->offset.y = cy + (zoom->offset.y - cy) * (new_zoom / zoom->value);
	zoom->value = new_zoom;
	apply_transform(fdf);
	render(fdf);
}

