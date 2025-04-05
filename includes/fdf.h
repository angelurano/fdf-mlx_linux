/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:25:48 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 09:55:33 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h> // open
# include <unistd.h> // close, read, write
# include <stdlib.h> // malloc, free
# include <stdio.h> // perror
# include <string.h> // strerror

# include <errno.h> // errno

# include <math.h> // math functions, -lm flag required in compilation

# include <stdint.h>

# include "mlx.h" // minilibx
# include "libft.h" // libft, gnl, printf

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}				t_vector3;

typedef struct s_color
{
	u_int8_t	t;
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
}				t_color;

typedef struct s_point
{
	t_vector3	coord;
	t_color		color;
}				t_point;

typedef struct s_points
{
	/*
	t_point		*points;
	size_t		capacity;
	size_t		size;
	*/
	t_dynarr	*buffer;
	size_t		lines;
	size_t		line_length;
}				t_points;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_fdf
{
	t_points	points;
}				t_fdf;

int		hexchar_to_dec(char c);
int		hexpair_to_dec(const char *s);
int		create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
t_color	create_color(uint8_t t, uint8_t r, uint8_t g, uint8_t b);

int		is_valid_filename(char *filename);
int		is_valid_color(char *str);
int		is_valid_value(char *str);

int		parse_input(t_fdf *fdf, char *filename);

#endif
