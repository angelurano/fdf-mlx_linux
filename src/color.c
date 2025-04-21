/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:29:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/21 19:18:31 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint8_t	blend_channel_gc(uint8_t fg, uint8_t bg, float a_fg)
{
	float	alpha;
	float	linear_fg;
	float	linear_bg;
	float	linear_color;

	alpha = 2.2f;
	linear_fg = pow(fg / 255.0f, alpha);
	linear_bg = pow(bg / 255.0f, alpha);
	linear_color = (linear_fg * a_fg + linear_bg * (1.0f - a_fg));
	return ((uint8_t)(pow(linear_color, 1 / alpha) * 255.0f + 0.5f));
}

t_pixel	blend_pixel(t_pixel fg, t_pixel bg)
{
	t_pixel	out;
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

t_pixel	apply_opacity(t_pixel color, float intensity)
{
	t_pixel	out;

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

t_pixel	lerp_color(t_pixel a, t_pixel b, float t)
{
	t_pixel	out;

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

void	swap_colors(t_pixel *a, t_pixel *b)
{
	t_pixel	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
t_pixel	blend_pixel(t_pixel fg, t_pixel bg)
{
	t_pixel	out;
	float	alpha_out;

	alpha_out = fg.a + bg.a * (1.0f - fg.a);
	if (alpha_out == 0.0f)
	{
		out.r = 0;
		out.g = 0;
		out.b = 0;
		out.a = 0;
		return (out);
	}
	out.r = (fg.r * fg.a + bg.r * bg.a * (1.0f - fg.a)) / alpha_out;
	out.g = (fg.g * fg.a + bg.g * bg.a * (1.0f - fg.a)) / alpha_out;
	out.b = (fg.b * fg.a + bg.b * bg.a * (1.0f - fg.a)) / alpha_out;
	out.a = alpha_out;
	return (out);
}
*/

uint32_t	get_argb(uint32_t a, uint32_t r, uint32_t g, uint32_t b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

t_pixel	get_pixel(uint32_t color)
{
	t_pixel	out;

	//out.a = ((color >> 24) & 0xFF) / 255.0f;
	out.a = (color >> 24) & 0xFF;
	out.r = (color >> 16) & 0xFF;
	out.g = (color >> 8) & 0xFF;
	out.b = color & 0xFF;
	return (out);
}

// endian = 0 little endian, endian = 1 big endian
unsigned int	get_rgb(int endian, uint8_t r, uint8_t g, uint8_t b)
{
	if (endian == 0)
		return ((255u << 24) | (r << 16) | (g << 8) | (b));
	return ((255u) | (r << 8) | (g << 16) | (b << 24));
}
