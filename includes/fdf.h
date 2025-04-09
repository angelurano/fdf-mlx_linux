/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:25:48 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/09 23:45:46 by migugar2         ###   ########.fr       */
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
# include <X11/X.h> // X11 interface, events, masks
# include <X11/keysym.h> // XK_* (keysyms)

# include "mlx.h" // minilibx
# include "libft.h" // libft, gnl, printf

# define HEIGHT 800
# define WIDTH 1000

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

typedef struct s_point
{
	t_vector3	coord;
	uint32_t	color;
}				t_point;

typedef struct s_pixel
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}				t_pixel;
/*
typedef struct s_pixel
{
	t_color	color;
}				t_pixel;
*/
typedef struct s_framebuffer
{
	t_pixel	*buffer;
	size_t	width;
	size_t	height;
}				t_framebuffer;

typedef struct s_points
{
	t_dynarr	*buffer;
	size_t		lines;
	size_t		line_length;
}				t_points;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}				t_img;

typedef struct s_camera
{
	float		zoom;
	float		z_scale;
	t_vector3	offset;
	float		rot_x;
	float		rot_y;
	float		rot_z;
}		t_camera;

typedef struct s_input
{
	char	key_up;
	char	key_down;
	char	key_left;
	char	key_right;
}				t_input;

typedef struct s_fdf
{
	void		*connection;
	void		*window;
	t_pixel		*framebuffer; // TODO
	t_img		img;
	t_points	points;
	t_camera	camera;
	t_input	input;
}				t_fdf;

int			is_valid_filename(char *filename);
int			is_valid_color(char *str);
int			is_number(char *str);
int			is_valid_value(char *str);

float		rad_to_deg(float rad);
float		deg_to_rad(float deg);
int			hexchar_to_dec(char c);
int			hex_to_dec(char *str, int len);

uint32_t	get_argb(uint32_t a, uint32_t r, uint32_t g, uint32_t b);
unsigned int	get_rgb(int endian, uint8_t r, uint8_t g, uint8_t b);
t_pixel		get_pixel(uint32_t color);
t_pixel		blend_pixel(t_pixel fg, t_pixel bg);

int			close_handler(t_fdf *fdf);
int			key_press_handler(int keysym, t_fdf *fdf);
int			key_release_handler(int keysym, t_fdf *fdf);
int			loop_handler(t_fdf *fdf);

t_list		*read_file(int fd);
u_int32_t	parse_color(char *value);
size_t		parse_value(t_fdf *fdf, char *value, float x, float y);
int			parse_line(t_fdf *fdf, char *line, int index);
int			parse_input(t_fdf *fdf, char *filename);

void		null_set_fdf(t_fdf *fdf);
void		init_data(t_fdf *fdf);
int			init_fdf(t_fdf *fdf);

void		render(t_fdf *fdf);
void		clear_framebuffer(t_fdf *fdf);

#endif
