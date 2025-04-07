/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:29:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/07 11:44:27 by migugar2         ###   ########.fr       */
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

uint32_t	get_argb(uint32_t a, uint32_t r, uint32_t g, uint32_t b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

// endian = 0 little endian, endian = 1 big endian
int	get_rgb(int endian, uint8_t r, uint8_t g, uint8_t b)
{
	if (endian == 0)
		return ((255 << 24) | (r << 16) | (g << 8) | (b));
	return ((255) | (r << 8) | (g << 16) | (b << 24));
}
