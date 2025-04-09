/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:39:27 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/07 12:00:32 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_filename(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
		return (0);
	if (ft_strcmp(dot, ".fdf") != 0)
		return (0);
	return (1);
}

int	is_valid_color(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (0);
	if (str[i] != '0' || str[i + 1] != 'x')
		return (0);
	i += 2;
	len = 0;
	while (str[i] && ft_isxdigit(str[i]))
	{
		len++;
		i++;
	}
	if (len != 6 && len != 4 && len != 3 && len != 2)
		return (0);
	if (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
		return (0);
	return (i);
}

int	is_number(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		len++;
		i++;
	}
	if (len == 0 || len > 10)
		return (0);
	return (i);
}

int	is_valid_value(char *str)
{
	size_t	i;
	size_t	color_len;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = is_number(str);
	if (i == 0)
		return (0);
	if (str[i] && str[i] == ',')
	{
		i++;
		color_len = is_valid_color(str + i);
		if (color_len == 0)
			return (0);
		i += color_len;
	}
	if (str[i] && str[i] != ' ' && str[i] != '\n')
		return (0);
	return (i);
}
