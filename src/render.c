/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:22:35 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/09 22:58:03 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_framebuffer(t_fdf *fdf)
{
	int	i;

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

void	plot_framebuffer_pixel(t_fdf *fdf, int x, int y, t_pixel color)
{
	t_pixel	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = &fdf->framebuffer[y * WIDTH + x];
	if (color.a == 0)
		return ;
	else
	{
		if (pixel->a == 0)
			ft_memcpy(pixel, &color, sizeof(t_pixel));
		else
			*pixel = blend_pixel(color, *pixel);
	}
}

void	draw_square(t_fdf *fdf, int x, int y, int len, t_pixel color)
{
	int	i;
	int	j;

	i = 0 - (len / 2);
	while (i < len / 2)
	{
		j = 0 - (len / 2);
		while (j < len / 2)
		{
			plot_framebuffer_pixel(fdf, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_circle(t_fdf *fdf, int x, int y, int radius, t_pixel color)
{
	int	i;
	int	j;
	int	sqr_radius;

	i = -radius;
	sqr_radius = radius * radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if ((i * i + j * j) <= sqr_radius)
				plot_framebuffer_pixel(fdf, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	tranform_to_img(t_fdf *fdf)
{
	int				i;
	int				j;
	unsigned int	*pixel;
	t_pixel			over_bg;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel = (unsigned int *)(fdf->img.pixels_ptr + (i
						* fdf->img.line_length + j * (fdf->img.bpp / 8)));
			over_bg = fdf->framebuffer[i * WIDTH + j];
			*pixel = get_rgb(fdf->img.endian, over_bg.r,
					over_bg.g, over_bg.b);
			j++;
		}
		i++;
	}
}

void	render(t_fdf *fdf)
{
	t_pixel	red = get_pixel(get_argb(128, 255, 0, 0));
	t_pixel	green = get_pixel(get_argb(128, 0, 255, 0));
	t_pixel	blue = get_pixel(get_argb(128, 0, 0, 255));

	/*
	printf("red: %u %u %u %f\n", red.r, red.g, red.b, red.a);
	printf("green: %u %u %u %f\n", green.r, green.g, green.b, green.a);
	printf("blue: %u %u %u %f\n", blue.r, blue.g, blue.b, blue.a);
	*/

	draw_circle(fdf, WIDTH / 2 - 50 + fdf->camera.offset.x, HEIGHT / 2 - 50 + fdf->camera.offset.y, 100, red);
	draw_circle(fdf, WIDTH / 2 + 50 + fdf->camera.offset.x, HEIGHT / 2 - 50 + fdf->camera.offset.y, 100, green);
	draw_circle(fdf, WIDTH / 2 + fdf->camera.offset.x, HEIGHT / 2 + 50 + fdf->camera.offset.y, 100, blue);
	tranform_to_img(fdf);
	mlx_clear_window(fdf->connection, fdf->window);
	mlx_put_image_to_window(fdf->connection, fdf->window,
		fdf->img.img_ptr, 0, 0);
	clear_framebuffer(fdf);
}
