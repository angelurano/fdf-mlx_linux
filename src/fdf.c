/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:20:37 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/09 18:11:35 by migugar2         ###   ########.fr       */
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
	// Create a new buffer with the size of the image, with info about rgba for each pixel
	// This buffer isn't the final image, it's a buffer to draw the image with alpha info per pixel
	render(&fdf);
	mlx_loop(fdf.connection);
	close_handler(&fdf);
}
