/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:36:47 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 17:02:20 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	null_set_fdf(t_fdf *fdf)
{
	fdf->connection = NULL;
	fdf->window = NULL;
	fdf->img.img_ptr = NULL;
	fdf->img.pixels_ptr = NULL;
	fdf->img.bpp = 0;
	fdf->img.endian = 0;
	fdf->img.line_length = 0;
	fdf->points.buffer = NULL;
	fdf->points.lines = 0;
	fdf->points.line_length = 0;
	fdf->zoom.offset.x = 0;
	fdf->zoom.offset.y = 0;
	fdf->zoom.value = 1.0f;
	fdf->zoom.factor = 1.05f;
	fdf->zoom.key_in = 0;
	fdf->zoom.key_out = 0;
}

void	init_events(t_fdf *fdf)
{
	mlx_hook(fdf->window,
		KeyPress,
		KeyPressMask,
		key_press_handler,
		fdf);
	mlx_hook(fdf->window,
		DestroyNotify,
		StructureNotifyMask,
		close_handler,
		fdf);
	mlx_hook(fdf->window,
		KeyRelease,
		KeyReleaseMask,
		key_release_handler,
		fdf);
	mlx_loop_hook(fdf->connection,
		loop_handler,
		fdf);
}

int	init_fdf(t_fdf *fdf)
{
	fdf->connection = mlx_init();
	if (fdf->connection == NULL)
		return (ft_printf_error("Error initializing connection\n"), 1);
	fdf->img.img_ptr = mlx_new_image(fdf->connection, WIDTH, HEIGHT);
	if (fdf->img.img_ptr == NULL)
		return (ft_printf_error("Error creating image\n"),
			mlx_destroy_display(fdf->connection), free(fdf->connection), 1);
	fdf->img.pixels_ptr = mlx_get_data_addr(fdf->img.img_ptr,
			&fdf->img.bpp, &fdf->img.line_length, &fdf->img.endian);
	if (fdf->img.pixels_ptr == NULL)
		return (ft_printf_error("Error getting image data address\n"),
			mlx_destroy_image(fdf->connection, fdf->img.img_ptr),
			mlx_destroy_display(fdf->connection), free(fdf->connection), 1);
	fdf->window = mlx_new_window(fdf->connection, WIDTH, HEIGHT, "FDF");
	if (fdf->window == NULL)
		return (ft_printf_error("Error creating window\n"),
			mlx_destroy_image(fdf->connection, fdf->img.img_ptr),
			free(fdf->connection), mlx_destroy_display(fdf->connection), 1);
	init_events(fdf);
	return (0);
}
