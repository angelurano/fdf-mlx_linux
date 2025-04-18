/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:53:07 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/18 07:28:33 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
void	float_line_v0(int x0, int y0, int x1, int y1)
{
	// ! PROBLEM: Only draw in positive x and positive y. Constantly do float operations, not exactly lines
	// deltas: difference between coords
	int	dx;
	int	dy;
	// m: slope, from dy / dx
	float	m;

	int	i;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx != 0)
	{
		m = dy / dx;
		i = 0;
		while (i <= dx)
		{
			// putPixel in (x, y) = (x0 + i, round(y0 + i * m))
			i++;
		}
	}
}
*/
/*
void	float_line(int x0, int y0, int x1, int y1)
{
	// ! PROBLEM: Constantly do float operations, not exactly lines
	// deltas
	int	dx;
	int	dy;
	// q of steps
	int	step;
	// size of each step
	float	step_x;
	float	step_y;

	int	i;

	dx = x1 - x0;
	dy = y1 - y0;
	step = max(abs(dx), abs(dy));
	if (step != 0)
	{
		step_x = dx / step;
		step_y = dy / step;
		i = 0;
		while (i <= step)
		{
			// putPixel in (x, y) = (round(x0 + i * step_x), round(y0 + i * step_y))
			i++;
		}
	}
}
*/
/*
void	bressenham_float_line(int x0, int y0, int x1, int y1)
{
	// ! PROBLEM: Not real bressenham, when using division constantly find floats, we need to simplify the operation removing the dx divisor in the slope (m)
	// deltas
	int	dx;
	int	dy;
	// m: slope
	float	m;
	// current y position
	int y;
	// py: exact y position for each x pixel
	float	py;
	// d0 is the difference between py and the current y in the x
	float d0;
	// d1 is the difference between py and the (y + 1) in the x
	float d1;

	int	i;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx != 0)
	{
		m = dy / dx;
		y = y0;
		i = 0;
		while (i <= dx)
		{
			* verbose version:
			// putPixel in (x0 + i, y)
			// py = m * (i + 1) + y0;
			// d0 = py - y;
			// d1 = (y + 1) - py;
			// if (d0 - d1 >= 0)
			// 	y += 1;
			// i++;

			* No verbose:
			// putPixel in (x0 + i, y)
			// p = ((m * (i + 1) + y0) - y) - ((y + 1) - (m * (i + 1) + y0))
			// p = m * (i + 1) + y0 - y - y - 1 + m * (i + 1) + y0
			p = 2 * m * (i + 1) + 2 * y0 - 2 * y - 1
			if (p >= 0)
				y += 1;
			i++;
		}
	}
}
*/
/*
planning for bressenham:
* where m = (dy/dx):
* p = 2*m*(i + 1) + 2*y0 - 2*y - 1
* p = 2*(dy/dx)*(i + 1) + 2*y0 - 2*y - 1
* p = dx*(2*(dy/dx)*(i + 1) + 2*y0 - 2*y - 1)
* p = 2*dy*(i + 1) + 2*y0*dx - 2*y*dx - dx
* p = 2*dy*i + 2*dy + 2*y0*dx - 2*y*dx - dx // <- non division p
* -- In the initial iteration, i must be 0, so 2*dy*0 must be 0, also y must be y0, so 2*y0*dx - 2*y*dx is 2*y0*dx - 2*y*dx in the first iteration, so, p initial is:
* p_initial = 0 + 2*dy + 0 - dx
* p_initial = 2*dy - dx
* -- also, in p, dy, dx, y0 must never change, so the values 2*dy, 2*y0*dx and -dx are constants, so, we can simplify the value of p like:
* p = 2*dy*i + 2*dy + 2*y0*dx - 2*y*dx - dx
* p = 2*dy*i - 2*y*dx
* p = 2*dy*i - 2*dx*y; // <- just prettier change
* -- p_next is the next point p
* p_next = 2*dy*(i + 1) - 2*dx*(y_next) // <- y_next is a var we don't know yet, must be the current y or y+1
* -- p_step is the size of the change from p to p_next
* p_step = p_next - p
* p_step = (2*dy*(i + 1) - 2*dx*(y_next)) - (2*dy*i - 2*dx*y)
* p_step = 2*dy*(i + 1) - 2*dy*i - 2*dx*(y_next) - 2*dx*y
* p_step = 2*dy*(i + 1 - i) - 2*dx*(y_next - y)
* -- p_increased, is the p more the p_step size when y_next is y+1
* p_increased = p + 2*dy*(i + 1 - i) - 2*dx*(y_next - y)
* p_increased = p + 2*dy*(i + 1 - i) - 2*dx*(y+1 - y)
* p_increased = p + 2*dy*(1) - 2*dx*(1)
* p_increased = p + 2*dy - 2*dx
* -- p_unchanged, is the p more the p_step size when y_next is y
* p_unchanged = p + 2*dy*(i + 1 - i) - 2*dx*(y_next - y)
* p_unchanged = p + 2*dy*(i + 1 - i) - 2*dx*(y - y)
* p_unchanged= p + 2*dy*(1) - 2*dx*(0)
* p_unchanged= p + 2*dy
void	bressenham_line_v0(int x0, int y0, int x1, int y1)
{
	// ! PROBLEM: Only draw in positive x and positive y
	// deltas
	int	dx;
	int	dy;
	// p: current point
	int	p;
	// y: current y position
	int	y;
	// i: current x position
	int i;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx != 0)
	{
		p = 2 * dy - dx; // <- initial p
		y = y0;
		i = 0;
		while (i <= dx)
		{
			// putPixel in (x. y) = (x0 + i, y)
			* Verbose:
			// if (p >= 0)
			// {
			// 	y += 1;
			// 	p = p + 2 * dy - 2 * dx;
			// }
			// else
			// 	p = p + 2 * dy;
			if (p >= 0)
			{
				y += 1;
				p -= 2 * dx; // <- p_unchanged
			}
			p += 2 * dy; // <- p_step
			i++;
		}
	}
}
*/
/*
void	bressenham_line_vertical(int x0, int y0, int x1, int y1)
{
	// Deltas
	int	dx;
	int	dy;
	// Directional :D
	int	dir;
	// p: current point
	int	p;
	// x: current x position
	int	x;
	// i: current y position
	int	i;

	if (y0 > y1)
	{
		i = y0;
		y0 = y1;
		y1 = i;
		i = x0;
		x0 = x1;
		x1 = i;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	dx *= dir;
	if (dy != 0)
	{
		p = 2 * dx - dy; // <- initial p
		x = x0;
		i = 0;
		while (i <= dy)
		{
			// putPixel in (x, y) = (x, y0 + i)
			if (p >= 0)
			{
				x += dir;
				p -= 2 * dy; // <- p_unchanged
			}
			p += 2 * dx; // <- p_step
			i++;
		}
	}
}
void	bressenham_line_horizontal(int x0, int y0, int x1, int y1)
{
	// Deltas
	int	dx;
	int	dy;
	// Directional :D
	int	dir;
	// p: current point
	int	p;
	// y: current y position
	int	y;
	// i: current x position
	int	i;

	if (x0 > x1)
	{
		i = x0;
		x0 = x1;
		x1 = i;
		i = y0;
		y0 = y1;
		y1 = i;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	dx = dx * dir;
	if (dx != 0)
	{
		p = 2 * dy - dx; // <- initial p
		y = y0;
		i = 0;
		while (i <= dx)
		{
			// putPixel in (x, y) = (x0 + i, y)
			if (p >= 0)
			{
				y += dir;
				p -= 2 * dx; // <- p_unchanged
			}
			p += 2 * dy; // <- p_step
			i++;
		}
	}
}
void	bressenham_line(int x0, int y0, int x1, int y1)
{
	if (abs(x1 - x0) > abs(y1 - y0))
		bressenham_line_horizontal(x0, y0, x1, y1);
	else
		bressenham_line_vertical(x0, y0, x1, y1);
}
*/
/*
void	bressenham_line(int x0, int y0, int x1, int y1)
{
	// ! PROBLEM: Draws aliased lines, pixels are really visual
	// Deltas
	int	dx;
	int	dy;
	// Directionals
	int	sx;
	int	sy;
	// Error: current point, called err because represents too
	int	err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if (x0 < x1)
		sx = 1;
	else
		sx = -1;

	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;
	while (1)
	{
		// putPixel in (x, y) = (x0, y0)
		if (x0 == x1 && y0 == y1)
			break ;
		if (err * 2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err * 2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
*/

/*
void	antialiasing_draw_line_v0(t_vector2 c0, t_vector2 c1)
{
	// ! PROBLEM: use floats, and only draw in positive x and positive y quadrant, don't treat different the first and last pixel
	// Deltas
	float	dx;
	float	dy;

	// m: slope (assuming dy/dx because of we are moving in x)
	float	m;

	int	floor_dx;
	int	i;

	// x and y are the current pixel position
	float	x;
	float	y;
	int	floor_x;
	int	floor_y;

	// distance from the pixel in exactly coord y in the imaginary line with the floor y, for known the opacity of the pixels based of the distance
	float distance;

	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	if (dx != 0)
	{
		m = dy / dx;
		floor_dx = (int)dx;
		i = 0;
		while (i <= floor_dx)
		{
			x = c0.x + i;
			y = c0.y + i * m;
			floor_x = (int)x;
			floor_y = (int)y;
			distance = y - floor_y;
			// putPixel in (x, y) = (floor_x, floor_y), with opactity = 1 - distance
			// putPixel in (x, y) = (floor_x, floor_y + 1), with opactity = distance
		}
	}
}
*/
/*
void	antialiasing_draw_line_verbose(t_vector2 c0, t_vector2 c1)
{
	// Deltas
	float	dx;
	float	dy;

	// m: slope (assuming dy/dx because of we are moving in x)
	float	m;

	int	floor_dx;
	int	i;

	// x and y are the current pixel position
	float	x;
	float	y;
	int	floor_x;
	int	floor_y;

	// distance
	float	distance;

	// overlap: from the i + x or y axis (iterated axis), the distance
	float	overlap;

	float	dis_start;
	float	dis_end;

	if (abs(c1.x - c0.x) < abs(c1.y - c0.y))
	{
		if (c0.x > c1.x)
		{
			t_vector2 tmp;

			tmp = c0;
			c0 = c1;
			c1 = tmp;
		}
		dx = c1.x - c0.x;
		dy = c1.y - c0.y;
		if (dx != 0)
		{
			m = dy / dx;
			floor_dx = (int)dx;

			overlap = 1 - ((c0.x + 0.5) - (int)(c0.x + 0.5));
			dis_start = c0.y - (int)c0.y;
			// putPixel in (x, y) = ((int)(c0.x + 0.5), (int)(c0.y)), with opactity = (1 - dis_start) * overlap
			// putPixel in (x, y) = ((int)(c0.x + 0.5), (int)(c0.y) + 1), with opactity = dis_start * overlap

			overlap = (c1.x + 0.5) - (int)(c1.x + 0.5);
			dis_end = c1.y - (int)c1.y;
			// putPixel in (x, y) = ((int)(c1.x + 0.5), (int)(c1.y)), with opactity = (1 - dis_end) * overlap
			// putPixel in (x, y) = ((int)(c1.x + 0.5), (int)(c1.y) + 1), with opactity = dis_end * overlap

			i = 1;
			while (i <= round(dx + 0.5))
			{
				x = c0.x + i;
				y = c0.y + i * m;
				floor_x = (int)x;
				floor_y = (int)y;
				distance = y - floor_y;
				// putPixel in (x, y) = (floor_x, floor_y), with opactity = 1 - distance
				// putPixel in (x, y) = (floor_x, floor_y + 1), with opactity = distance
			}
		}
	}
	else
	{
		if (c0.y > c1.y)
		{
			t_vector2 tmp;

			tmp = c0;
			c0 = c1;
			c1 = tmp;
		}
		dx = c1.x - c0.x;
		dy = c1.y - c0.y;
		if (dy != 0)
		{
			m = dx / dy;
			floor_dx = (int)dy;

			overlap = 1 - ((c0.y + 0.5) - (int)(c0.y + 0.5));
			dis_start = c0.x - (int)c0.x;
			// putPixel in (x, y) = ((int)(c0.x), (int)(c0.y + 0.5)), with opactity = (1 - dis_start) * overlap
			// putPixel in (x, y) = ((int)(c0.x) + 1, (int)(c0.y + 0.5)), with opactity = dis_start * overlap

			overlap = (c1.y + 0.5) - (int)(c1.y + 0.5);
			dis_end = c1.x - (int)c1.x;
			// putPixel in (x, y) = ((int)(c1.x), (int)(c1.y + 0.5)), with opactity = (1 - dis_end) * overlap
			// putPixel in (x, y) = ((int)(c1.x) + 1, (int)(c1.y + 0.5)), with opactity = dis_end * overlap

			i = 1;
			while (i <= round(dy + 0.5))
			{
				x = c0.x + i * m;
				y = c0.y + i;
				floor_x = (int)x;
				floor_y = (int)y;
				distance = x - floor_x;
				// putPixel in (x, y) = (floor_x, floor_y), with opactity = 1 - distance
				// putPixel in (x, y) = (floor_x + 1, floor_y), with opactity = distance
			}
		}
	}

}
*/

typedef struct s_wu_line
{
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

void	ft_swap(int *a, int *b)
{
	int	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swapf(float *a, float *b)
{
	float	tmp = *a;
	*a = *b;
	*b = tmp;
}

static float	frac_part(float x)
{
	return (x - floorf(x));
}

static int	round_to_int(float x)
{
	return ((int)(floorf(x + 0.5f)));
}

static void	set_wu_line(t_wu_line *line, t_vector2 p0, t_vector2 p1)
{
	line->is_steep = fabsf(p1.y - p0.y) > fabsf(p1.x - p0.x);
	if (line->is_steep)
	{
		line->x0s = p0.y;
		line->y0s = p0.x;
		line->x1s = p1.y;
		line->y1s = p1.x;
	}
	else
	{
		line->x0s = p0.x;
		line->y0s = p0.y;
		line->x1s = p1.x;
		line->y1s = p1.y;
	}
	if (line->x0s > line->x1s)
	{
		ft_swapf(&line->x0s, &line->x1s);
		ft_swapf(&line->y0s, &line->y1s);
	}
	line->dx = line->x1s - line->x0s;
	line->dy = line->y1s - line->y0s;
	line->gradient = 1.0f;
	if (line->dx != 0)
		line->gradient = line->dy / line->dx;
}

static void	draw_first_endpoint(t_fdf *fdf, t_wu_line *line, t_pixel color)
{
	float	i1;
	float	i2;

	line->x_pixel1 = round_to_int(line->x0s);
	line->yend = line->y0s + line->gradient * (line->x_pixel1 - line->x0s);
	line->y_pixel1 = (int)floorf(line->yend);
	line->xgap = 1.0f - frac_part(line->x0s + 0.5f);
	i1 = (1.0f - frac_part(line->yend)) * line->xgap;
	i2 = frac_part(line->yend) * line->xgap;
	if (line->is_steep)
	{
		plot_framebuffer_pixel(fdf, line->y_pixel1, line->x_pixel1, apply_opacity(color, i1));
		plot_framebuffer_pixel(fdf, line->y_pixel1 + 1, line->x_pixel1, apply_opacity(color, i2));
	}
	else
	{
		plot_framebuffer_pixel(fdf, line->x_pixel1, line->y_pixel1, apply_opacity(color, i1));
		plot_framebuffer_pixel(fdf, line->x_pixel1, line->y_pixel1 + 1, apply_opacity(color, i2));
	}
}

static void	draw_middle_pixels(t_fdf *fdf, t_wu_line *line, t_pixel color)
{
	while (line->x < line->max_x)
	{
		line->y = (int)floorf(line->intery);
		float i_lower = 1.0f - frac_part(line->intery);
		float i_upper = frac_part(line->intery);

		if (line->is_steep)
		{
			plot_framebuffer_pixel(fdf, line->y, line->x, apply_opacity(color, i_lower));
			plot_framebuffer_pixel(fdf, line->y + 1, line->x, apply_opacity(color, i_upper));
		}
		else
		{
			plot_framebuffer_pixel(fdf, line->x, line->y, apply_opacity(color, i_lower));
			plot_framebuffer_pixel(fdf, line->x, line->y + 1, apply_opacity(color, i_upper));
		}
		line->intery += line->gradient;
		line->x++;
	}
}

static void	draw_last_endpoint(t_fdf *fdf, t_wu_line *line, t_pixel color)
{
	float	i1;
	float	i2;

	line->x_pixel2 = round_to_int(line->x1s);
	line->yend2 = line->y1s + line->gradient * (line->x_pixel2 - line->x1s);
	line->y_pixel2 = (int)floorf(line->yend2);
	line->xgap2 = frac_part(line->x1s + 0.5f);
	i1 = (1.0f - frac_part(line->yend2)) * line->xgap2;
	i2 = frac_part(line->yend2) * line->xgap2;
	if (line->is_steep)
	{
		plot_framebuffer_pixel(fdf, line->y_pixel2, line->x_pixel2, apply_opacity(color, i1));
		plot_framebuffer_pixel(fdf, line->y_pixel2 + 1, line->x_pixel2, apply_opacity(color, i2));
	}
	else
	{
		plot_framebuffer_pixel(fdf, line->x_pixel2, line->y_pixel2, apply_opacity(color, i1));
		plot_framebuffer_pixel(fdf, line->x_pixel2, line->y_pixel2 + 1, apply_opacity(color, i2));
	}
}

void	draw_wu_line(t_fdf *fdf, t_vector2 p0, t_vector2 p1, t_pixel color)
{
	t_wu_line	line;

	set_wu_line(&line, p0, p1);
	draw_first_endpoint(fdf, &line, color);
	line.intery = line.yend + line.gradient;
	line.min_x = line.x_pixel1 + 1;
	line.max_x = round_to_int(line.x1s);
	line.x = line.min_x;
	draw_middle_pixels(fdf, &line, color);
	draw_last_endpoint(fdf, &line, color);
}
