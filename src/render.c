/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:22:35 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/18 19:23:28 by migugar2         ###   ########.fr       */
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
		fdf->framebuffer[i].a = 0;
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

void draw_example_lines(t_fdf *fdf, t_pixel color1, t_pixel color2)
{
	// Centro de la pantalla con offset
	int cx = WIDTH  / 2 + (int)fdf->camera.offset.x;
	int cy = HEIGHT / 2 + (int)fdf->camera.offset.y;
	t_vector2 p0, p1;

	p0.x = (float)cx;
	p0.y = (float)cy;

	// ——— Línea a 30° ———
	p1.x = (int)(p0.x + cosf(30.0f * (M_PI / 180.0f)) * 150.0f);  // longitud 150 px
	p1.y = (int)(p0.y + sinf(30.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 60° ———
	p1.x = (int)(p0.x + cosf(60.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(60.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 120° ———
	p1.x = (int)(p0.x + cosf(120.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(120.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 150° ———
	p1.x = (int)(p0.x + cosf(150.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(150.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 210° ———
	p1.x = (int)(p0.x + cosf(210.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(210.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 240° ———
	p1.x = (int)(p0.x + cosf(240.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(240.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 300° ———
	p1.x = (int)(p0.x + cosf(300.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(300.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);

	// ——— Línea a 330° ———
	p1.x = (int)(p0.x + cosf(330.0f * (M_PI / 180.0f)) * 150.0f);
	p1.y = (int)(p0.y + sinf(330.0f * (M_PI / 180.0f)) * 150.0f);
	draw_line(fdf, p0, p1, color1, color2);
}

void draw_fan_lines(t_fdf *fdf, t_pixel color1, t_pixel color2)
{
	const int start_x = WIDTH / 2 + (int)fdf->camera.offset.x;
	const int start_y = 10 + (int)fdf->camera.offset.y;
	const int spacing = 35; // Espacio entre líneas
	const int max_offset = WIDTH / 2;

	for (int offset = -max_offset; offset <= max_offset; offset += spacing)
	{
		t_vector2 end = { .x = start_x + offset, .y = HEIGHT - 1 };

		t_vector2 start = { .x = start_x, .y = start_y };

		draw_line(fdf, start, end, color1, color2);
	}
}

void	render(t_fdf *fdf)
{
	t_pixel	red = get_pixel(get_argb(255, 255, 0, 0));
	t_pixel	green = get_pixel(get_argb(255, 0, 255, 0));
	t_pixel	blue = get_pixel(get_argb(255, 0, 0, 255));
	(void)red;
	(void)green;
	(void)blue;

	// draw_circle(fdf, WIDTH / 2 - 50 + fdf->camera.offset.x, HEIGHT / 2 - 50 + fdf->camera.offset.y, 100, red);
	// draw_circle(fdf, WIDTH / 2 + 50 + fdf->camera.offset.x, HEIGHT / 2 - 50 + fdf->camera.offset.y, 100, green);
	// draw_circle(fdf, WIDTH / 2 + fdf->camera.offset.x, HEIGHT / 2 + 50 + fdf->camera.offset.y, 100, blue);
	// draw_example_lines(fdf, red, blue);
	draw_fan_lines(fdf, red, blue);
	tranform_to_img(fdf);
	mlx_clear_window(fdf->connection, fdf->window);
	mlx_put_image_to_window(fdf->connection, fdf->window,
		fdf->img.img_ptr, 0, 0);
	clear_framebuffer(fdf);
}
