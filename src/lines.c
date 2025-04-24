/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:53:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/24 13:47:21 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_wu_line(t_wu_line *line, t_vec2 p0, t_vec2 p1)
{
	if (line->is_steep)
	{
		line->x0s = p0.y;
		line->y0s = p0.x;
		line->x1s = p1.y;
		line->y1s = p1.x;
	}
	else
	{
		line->x0s = p0.x;
		line->y0s = p0.y;
		line->x1s = p1.x;
		line->y1s = p1.y;
	}
	if (line->x0s > line->x1s)
	{
		ft_swapf(&line->x0s, &line->x1s);
		ft_swapf(&line->y0s, &line->y1s);
		swap_colors(&line->c0, &line->c1);
	}
	line->dx = line->x1s - line->x0s;
	line->dy = line->y1s - line->y0s;
	line->gradient = 1.0f;
	if (line->dx != 0)
		line->gradient = line->dy / line->dx;
}

static void	draw_first_endpoint(t_fdf *fdf, t_wu_line *line)
{
	t_color	c0;
	float	i1;
	float	i2;

	c0 = line->c0;
	line->x_pixel1 = roundf_to_int(line->x0s);
	line->yend = line->y0s + line->gradient * (line->x_pixel1 - line->x0s);
	line->y_pixel1 = (int)floorf(line->yend);
	line->xgap = 1.0f - frac_part(line->x0s + 0.5f);
	i1 = (1.0f - frac_part(line->yend)) * line->xgap;
	i2 = frac_part(line->yend) * line->xgap;
	if (line->is_steep)
	{
		plot_framebuffer_pixel(fdf, line->y_pixel1, line->x_pixel1,
			set_opacity(c0, i1));
		plot_framebuffer_pixel(fdf, line->y_pixel1 + 1, line->x_pixel1,
			set_opacity(c0, i2));
	}
	else
	{
		plot_framebuffer_pixel(fdf, line->x_pixel1, line->y_pixel1,
			set_opacity(c0, i1));
		plot_framebuffer_pixel(fdf, line->x_pixel1, line->y_pixel1 + 1,
			set_opacity(c0, i2));
	}
}

static void	draw_mid_pixels(t_fdf *fdf, t_wu_line *line, t_color c0, t_color c1)
{
	t_color	interpolated;

	while (line->x < line->max_x)
	{
		line->y = (int)floorf(line->intery);
		interpolated = lerp_color(c0, c1, (line->x - line->x0s) / line->dx);
		if (line->is_steep)
		{
			plot_framebuffer_pixel(fdf, line->y, line->x,
				set_opacity(interpolated, 1.0f - frac_part(line->intery)));
			plot_framebuffer_pixel(fdf, line->y + 1, line->x,
				set_opacity(interpolated, frac_part(line->intery)));
		}
		else
		{
			plot_framebuffer_pixel(fdf, line->x, line->y,
				set_opacity(interpolated, 1.0f - frac_part(line->intery)));
			plot_framebuffer_pixel(fdf, line->x, line->y + 1,
				set_opacity(interpolated, frac_part(line->intery)));
		}
		line->intery += line->gradient;
		line->x++;
	}
}

static void	draw_last_endpoint(t_fdf *fdf, t_wu_line *line)
{
	float	i1;
	float	i2;
	t_color	c1;

	c1 = line->c1;
	line->x_pixel2 = roundf_to_int(line->x1s);
	line->yend2 = line->y1s + line->gradient * (line->x_pixel2 - line->x1s);
	line->y_pixel2 = (int)floorf(line->yend2);
	line->xgap2 = frac_part(line->x1s + 0.5f);
	i1 = (1.0f - frac_part(line->yend2)) * line->xgap2;
	i2 = frac_part(line->yend2) * line->xgap2;
	if (line->is_steep)
	{
		plot_framebuffer_pixel(fdf, line->y_pixel2, line->x_pixel2,
			set_opacity(c1, i1));
		plot_framebuffer_pixel(fdf, line->y_pixel2 + 1, line->x_pixel2,
			set_opacity(c1, i2));
	}
	else
	{
		plot_framebuffer_pixel(fdf, line->x_pixel2, line->y_pixel2,
			set_opacity(c1, i1));
		plot_framebuffer_pixel(fdf, line->x_pixel2, line->y_pixel2 + 1,
			set_opacity(c1, i2));
	}
}

void	draw_line(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	t_wu_line	line;

	line.c0 = v0.color;
	line.c1 = v1.color;
	line.is_steep = fabsf(v1.screen.y - v0.screen.y)
		> fabsf(v1.screen.x - v0.screen.x);
	set_wu_line(&line, v0.screen, v1.screen);
	draw_first_endpoint(fdf, &line);
	line.intery = line.yend + line.gradient;
	line.min_x = line.x_pixel1 + 1;
	line.max_x = roundf_to_int(line.x1s);
	line.x = line.min_x;
	draw_mid_pixels(fdf, &line, line.c0, line.c1);
	draw_last_endpoint(fdf, &line);
}
