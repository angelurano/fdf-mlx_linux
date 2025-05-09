/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:22:35 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/03 22:50:16 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_fdf *fdf)
{
	unsigned int	*pixel;
	unsigned int	color;
	size_t			i;
	size_t			j;

	color = pack_color(fdf->img.endian, color_rgba(0, 0, 0, 255));
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel = (unsigned int *)(fdf->img.pixels_ptr + (i
						* fdf->img.line_length + j * (fdf->img.bpp / 8)));
			*pixel = color;
			j++;
		}
		i++;
	}
}

void	plot_image_pixel(t_fdf *fdf, int x, int y, t_color color)
{
	unsigned int	*pixel;
	t_color			bg_color;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || color.a == 0)
		return ;
	pixel = (unsigned int *)(fdf->img.pixels_ptr + (y
				* fdf->img.line_length + x * (fdf->img.bpp / 8)));
	bg_color = unpack_color(fdf->img.endian, *pixel);
	*pixel = pack_color(fdf->img.endian,
			blend_pixel(color, bg_color));
}

static void	draw(t_fdf *fdf)
{
	t_vertex	*v;
	size_t		i;
	size_t		j;
	size_t		idx;

	v = ft_dynarrget(fdf->points.buffer, 0);
	i = 0;
	while (i < fdf->points.lines)
	{
		j = fdf->points.line_length;
		while (j > 0)
		{
			j--;
			idx = (i * fdf->points.line_length) + j;
			if (i + 1 < fdf->points.lines)
				draw_line(fdf, v[idx], v[idx + fdf->points.line_length]);
			if (j > 0 && j - 1 < fdf->points.line_length)
				draw_line(fdf, v[idx], v[idx - 1]);
		}
		i++;
	}
}

void	render(t_fdf *fdf)
{
	clear_image(fdf);
	draw(fdf);
	mlx_clear_window(fdf->connection, fdf->window);
	mlx_put_image_to_window(fdf->connection, fdf->window,
		fdf->img.img_ptr, 0, 0);
}
