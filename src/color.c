/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:29:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 09:44:14 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hexchar_to_dec(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (0);
}

int	hexpair_to_dec(const char *s)
{
	return (hexchar_to_dec(s[0]) * 16 + hexchar_to_dec(s[1]));
}

int	create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

t_color	create_color(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	t_color	color;

	color.t = t;
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
