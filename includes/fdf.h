/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:25:48 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/27 01:24:11 by migugar2         ###   ########.fr       */
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

typedef struct s_vec2
{
	float	x;
	float	y;
}				t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_color
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}				t_color;

typedef struct s_vertex
{
	t_vec3	coord;
	t_vec2	screen;
	t_color	color;
}				t_vertex;

// t_dynarr points to t_vertex
typedef struct s_mesh
{
	t_dynarr	*buffer;
	size_t		lines;
	size_t		line_length;
}				t_mesh;

typedef struct s_mlx_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx_img;

typedef struct s_fdf
{
	void			*connection;
	void			*window;
	t_color			*framebuffer; // framebuffer is 1D with width * height
	t_mlx_img		img;
	t_mesh			points;
}				t_fdf;

int			is_valid_filename(char *filename);
int			is_valid_color(char *str);
int			is_number(char *str);
int			is_valid_value(char *str);

float		rad_to_deg(float rad);
float		deg_to_rad(float deg);
int			hexchar_to_dec(char c);
int			hex_to_dec(char *str, int len);
int			roundf_to_int(float x);
float		frac_part(float x);

int			hexchar_color(char c);
uint32_t	get_argb(uint32_t a, uint32_t r, uint32_t g, uint32_t b);
unsigned int	get_rgb(int endian, uint8_t r, uint8_t g, uint8_t b);
t_color		get_color(uint32_t color);
t_color		color_argb(uint32_t a, uint32_t r, uint32_t g, uint32_t b);
t_color		blend_pixel(t_color fg, t_color bg);
t_color		set_opacity(t_color color, float intensity);
t_color		lerp_color(t_color a, t_color b, float t);
void		swap_colors(t_color *a, t_color *b);

int			close_handler(t_fdf *fdf);
int			key_press_handler(int keysym, t_fdf *fdf);

t_list		*read_file(int fd);
t_color		parse_color(char *value);
size_t		parse_value(t_fdf *fdf, char *value, float x, float y);
int			parse_line(t_fdf *fdf, char *line, int index);
int			parse_input(t_fdf *fdf, char *filename);

void		null_set_fdf(t_fdf *fdf);
void		init_framebuffer(t_fdf *fdf);
int			init_fdf(t_fdf *fdf);

void		plot_framebuffer_pixel(t_fdf *fdf, int x, int y, t_color color);

void		project_vertex_iso(t_vertex *point);

typedef struct s_wu_line
{
	t_color	c0;
	t_color	c1;
	int		is_steep;
	float	x0s;
	float	y0s;
	float	x1s;
	float	y1s;
	int		x_pixel1;
	int		y_pixel1;
	int		x_pixel2;
	int		y_pixel2;
	float	dx;
	float	dy;
	float	gradient;
	float	intery;
	float	xgap;
	float	xgap2;
	float	yend;
	float	yend2;
	int		x;
	int		y;
	int		max_x;
	int		min_x;
	int		min_y;
}	t_wu_line;

void		draw_line(t_fdf *fdf, t_vertex v0, t_vertex v1);

void		render(t_fdf *fdf);

#endif
