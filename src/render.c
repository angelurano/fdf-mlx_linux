/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:22:35 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/29 20:56:44 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_framebuffer_pixel(t_fdf *fdf, int x, int y, t_color color)
{
	t_color	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = &fdf->framebuffer[y * WIDTH + x];
	if (color.a == 0)
		return ;
	else
		*pixel = blend_pixel(color, *pixel);
}

void	tranform_to_img(t_fdf *fdf)
{
	int				i;
	int				j;
	unsigned int	*pixel;
	t_color			color;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel = (unsigned int *)(fdf->img.pixels_ptr + (i
						* fdf->img.line_length + j * (fdf->img.bpp / 8)));
			color = fdf->framebuffer[i * WIDTH + j];
			*pixel = get_rgb(fdf->img.endian, color.r,
					color.g, color.b);
			j++;
		}
		i++;
	}
}

void	draw(t_fdf *fdf)
{
	t_vertex	*v;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < fdf->points.lines)
	{
		j = 0;
		while (j < fdf->points.line_length)
		{
			v = ft_dynarrget(fdf->points.buffer,
					i * fdf->points.line_length + j);
			if (i + 1 < fdf->points.lines)
				draw_line(fdf, *v, *(t_vertex *)ft_dynarrget(fdf->points.buffer,
						(i + 1) * fdf->points.line_length + j));
			if (j + 1 < fdf->points.line_length)
				draw_line(fdf, *v, *(t_vertex *)ft_dynarrget(fdf->points.buffer,
						i * fdf->points.line_length + j + 1));
			j++;
		}
		i++;
	}
}

void	clear_framebuffer(t_fdf *fdf)
{
	size_t	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		fdf->framebuffer[i].r = 0;
		fdf->framebuffer[i].g = 0;
		fdf->framebuffer[i].b = 0;
		fdf->framebuffer[i].a = 255;
		i++;
	}
}

// TODO: remove this function
void	print_input(t_fdf *fdf)
{
	size_t		i;
	size_t		j;
	t_vertex	*v;

	i = 0;
	while (i < fdf->points.lines)
	{
		j = 0;
		while (j < fdf->points.line_length)
		{
			v = ft_dynarrget(fdf->points.buffer,
					i * fdf->points.line_length + j);
			printf("x: %f y: %f z: %f color: (r: %u g: %u b: %u a: %u)\n",
				v->coord.x, v->coord.y, v->coord.z, v->color.r, v->color.g, v->color.b, v->color.a);
			j++;
		}
		i++;
	}
}

void	render(t_fdf *fdf)
{
	clear_framebuffer(fdf);
	draw(fdf);
	tranform_to_img(fdf);
	mlx_clear_window(fdf->connection, fdf->window);
	mlx_put_image_to_window(fdf->connection, fdf->window,
		fdf->img.img_ptr, 0, 0);
}

// TODO: norm and full refactor, implement queue for bfs?, for bonus can be in the quick sort
/*
void	draw(t_fdf *fdf)
{
	size_t	i;
	size_t	j;
	t_vertex	*v0;
	t_vertex	*v1;

	i = 0;
	v0 = ft_dynarrget(fdf->points.buffer, 0);
	project_vertex_iso(v0);
	while (i < fdf->points.lines)
	{
		j = 0;
		while (j < fdf->points.line_length)
		{
			v0 = ft_dynarrget(fdf->points.buffer,
					i * fdf->points.line_length + j);
			if (i + 1 < fdf->points.lines)
			{
				v1 = ft_dynarrget(fdf->points.buffer,
						(i + 1) * fdf->points.line_length + j);
				project_vertex_iso(v1);
				draw_line(fdf, *v0, *v1);
			}
			if (j + 1 < fdf->points.line_length)
			{
				v1 = ft_dynarrget(fdf->points.buffer,
						i * fdf->points.line_length + j + 1);
				project_vertex_iso(v1);
				draw_line(fdf, *v0, *v1);
			}
			j++;
		}
		i++;
	}
}
*/
