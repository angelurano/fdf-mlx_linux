/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_endian.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:21:57 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 18:24:09 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	t_color	out;

	out.r = r;
	out.g = g;
	out.b = b;
	out.a = a;
	return (out);
}

uint32_t	pack_color(int endian, t_color color)
{
	uint32_t	packed;

	if (endian == 0)
		packed = (((uint32_t)color.a << 24)
				| (color.r << 16) | (color.g << 8) | color.b);
	else
		packed = ((color.a) | (color.r << 8) | (color.g << 16)
				| ((uint32_t)color.b << 24));
	return (packed);
}

t_color	unpack_color(int endian, uint32_t packed)
{
	t_color	color;

	if (endian == 0)
	{
		color.a = (packed >> 24) & 0xFF;
		color.r = (packed >> 16) & 0xFF;
		color.g = (packed >> 8) & 0xFF;
		color.b = packed & 0xFF;
	}
	else
	{
		color.a = packed & 0xFF;
		color.r = (packed >> 8) & 0xFF;
		color.g = (packed >> 16) & 0xFF;
		color.b = (packed >> 24) & 0xFF;
	}
	return (color);
}
