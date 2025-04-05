/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:25:48 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 11:59:50 by migugar2         ###   ########.fr       */
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

# include <stdint.h> // int & u int types

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
	u_int8_t	a;
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

int			is_valid_filename(char *filename);
int			is_valid_color(char *str);
int			is_number(char *str);
int			is_valid_value(char *str);

int			hexchar_to_dec(char c);
int			hexpair_to_dec(const char *s);
uint32_t	get_argb(int a, int r, int g, int b);
t_color		create_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
uint32_t	convert_color(t_color color);

t_list		*read_file(int fd);
t_color		parse_color(char *value);
size_t		parse_value(t_fdf *fdf, char *value, float x, float y);
int			parse_line(t_fdf *fdf, char *line, int index);
int			parse_input(t_fdf *fdf, char *filename);

#endif
