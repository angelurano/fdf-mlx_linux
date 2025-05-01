/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:29:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 18:41:04 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_colors(t_color *a, t_color *b)
{
	t_color	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static uint8_t	blend_channel_gc(uint8_t fg, uint8_t bg, float a_fg)
{
	float	linear_fg;
	float	linear_bg;
	float	linear_color;
	float	tmp;

	tmp = fg / 255.0f;
	linear_fg = tmp * tmp;
	tmp = bg / 255.0f;
	linear_bg = tmp * tmp;
	linear_color = (linear_fg * a_fg + linear_bg * (1.0f - a_fg));
	return ((uint8_t)(powf(linear_color, 0.5f) * 255.0f + 0.5f));
}

t_color	blend_pixel(t_color fg, t_color bg)
{
	t_color	out;
	float	a_fg;
	float	a_bg;
	float	a_out;

	a_fg = fg.a / 255.0f;
	a_bg = bg.a / 255.0f;
	a_out = a_fg + a_bg * (1.0f - a_fg);
	if (a_out == 0.0f)
	{
		out.r = 0;
		out.g = 0;
		out.b = 0;
		out.a = 0;
		return (out);
	}
	out.r = blend_channel_gc(fg.r, bg.r, a_fg);
	out.g = blend_channel_gc(fg.g, bg.g, a_fg);
	out.b = blend_channel_gc(fg.b, bg.b, a_fg);
	out.a = (uint8_t)(a_out * 255.0f + 0.5f);
	return (out);
}

t_color	set_opacity(t_color color, float intensity)
{
	t_color	out;

	out.r = color.r;
	out.g = color.g;
	out.b = color.b;
	if (intensity <= 0.0f)
		out.a = 0;
	else if (intensity >= 1.0f)
		out.a = 255;
	else
		out.a = (uint8_t)(color.a * intensity + 0.5f);
	return (out);
}

t_color	lerp_color(t_color a, t_color b, float t)
{
	t_color	out;

	out.r = (uint8_t)(a.r + (b.r - a.r) * t + 0.5f);
	out.g = (uint8_t)(a.g + (b.g - a.g) * t + 0.5f);
	out.b = (uint8_t)(a.b + (b.b - a.b) * t + 0.5f);
	if (t <= 0.0f)
		out.a = a.a;
	else if (t >= 1.0f)
		out.a = b.a;
	else
		out.a = (uint8_t)(a.a + (b.a - a.a) * t + 0.5f);
	return (out);
}
