/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:13:05 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/27 01:00:51 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	rad_to_deg(float rad)
{
	return (rad * (180.0 / M_PI));
}

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180.0));
}

float	frac_part(float x)
{
	return (x - floorf(x));
}

int	roundf_to_int(float x)
{
	return ((int)(floorf(x + 0.5f)));
}

int	hexchar_to_dec(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	else if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (0);
}

int	hex_to_dec(char *str, int len)
{
	int	dec;
	int	i;

	dec = 0;
	i = 0;
	while (str && str[i] && i < len)
	{
		dec *= 16;
		dec += hexchar_to_dec(str[i]);
		i++;
	}
	return (dec);
}
