/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:20:37 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 17:40:03 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		return (ft_printf_error("Usage: %s <map.fdf>\n", argv[0]), 1);
	null_set_fdf(&fdf);
	if (parse_input(&fdf, argv[1]))
		return (1);
	if (init_fdf(&fdf))
		return (ft_printf_error("Error initializing FDF\n"),
			ft_dynarrfree(&fdf.points.buffer, NULL), 1);
	mlx_loop(fdf.connection);
	close_handler(&fdf);
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
