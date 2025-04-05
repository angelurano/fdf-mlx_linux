/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:25:48 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 12:52:24 by migugar2         ###   ########.fr       */
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

# define HEIGHT 600
# define WIDTH 800

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif

# ifndef M_PI_4
#  define M_PI_4 0.78539816339744830962
# endif

typedef struct s_vector2
{
	float	x;
	float	y;
}				t_vector2;

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
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}				t_data;

typedef struct s_camera
{
	float		zoom;
	float		z_scale;
	t_vector3	offset;
	float		rot_x;
	float		rot_y;
	float		rot_z;
}		t_camera;

typedef struct s_fdf
{
	void		*connection;
	void		*window;
	t_data		img;
	t_camera	camera;
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

void		null_set_fdf(t_fdf *fdf);
void		init_data(t_fdf *fdf);
int			init_fdf(t_fdf *fdf);

#endif
