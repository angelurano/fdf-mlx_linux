/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:29:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/18 06:58:29 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	out.r = (uint8_t)(((fg.r * a_fg + bg.r * a_bg * (1.0f - a_fg)) / a_out)
			+ 0.5f);
	out.g = (uint8_t)(((fg.g * a_fg + bg.g * a_bg * (1.0f - a_fg)) / a_out)
			+ 0.5f);
	out.b = (uint8_t)(((fg.b * a_fg + bg.b * a_bg * (1.0f - a_fg)) / a_out)
			+ 0.5f);
	out.a = (uint8_t)(a_out * 255.0f + 0.5f);
	return (out);
}

t_pixel	apply_opacity(t_pixel color, float intensity)
{
	t_pixel	out;

	out.r = (uint8_t)(color.r * intensity);
	out.g = (uint8_t)(color.g * intensity);
	out.b = (uint8_t)(color.b * intensity);
	if (intensity <= 0.0f)
		out.a = 0;
	else if (intensity >= 1.0f)
		out.a = 255;
	else
		out.a = (uint8_t)(color.a * intensity + 0.5f);
	return (out);
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
