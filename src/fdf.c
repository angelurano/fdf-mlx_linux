/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:20:37 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 10:46:42 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		return (ft_printf_error("Usage: %s <map.fdf>\n", argv[0]), 1);
	if (parse_input(&fdf, argv[1]))
		return (1);
	printf("Points: %zu\n", fdf.points.buffer->size);
	printf("Capacity: %zu\n", fdf.points.buffer->capacity);
	printf("Lines: %zu\n", fdf.points.lines);
	printf("Line length: %zu\n", fdf.points.line_length);
	/*
	for (size_t i = 0; i < fdf.points.lines * fdf.points.line_length; i++)
	{
		t_point *point = ft_dynarrget(fdf.points.buffer, i);
		if (point)
			printf("Point %zu: (%f, %f, %f) Color rgba: (%u, %u, %u, %u)\n", i,
				point->coord.x, point->coord.y, point->coord.z,
				point->color.r, point->color.g, point->color.b, point->color.t);
	}
	*/
	ft_dynarrfree(&fdf.points.buffer, NULL);
	/*
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	ft_printf("Starting FDF!\n");

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 100, 100, 0x00FF0000); // ARGB: Alpha, Red, Green, Blue
	my_mlx_square_put(&img, 200, 200, 50, 0x0000FF00); // ARGB: Alpha, Red, Green, Blue
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
	*/
}
