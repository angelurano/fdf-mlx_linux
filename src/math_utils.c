/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:13:05 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 16:58:48 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	hexchar_color(char c)
{
	int	dec;

	dec = hexchar_to_dec(c);
	if (dec <= 0 || dec > 15)
		return (0);
	dec++;
	return (dec * dec - 1);
}
