/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:27:54 by migugar2          #+#    #+#             */
/*   Updated: 2025/05/01 18:42:34 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_handler(t_fdf *fdf)
{
	mlx_destroy_window(fdf->connection, fdf->window);
	mlx_destroy_image(fdf->connection, fdf->img.img_ptr);
	mlx_destroy_display(fdf->connection);
	free(fdf->connection);
	ft_dynarrfree(&fdf->points.buffer, NULL);
	exit(0);
	return (0);
}

int	key_press_handler(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		return (close_handler(fdf));
	else if (keysym == XK_plus)
		fdf->zoom.key_in = 1;
	else if (keysym == XK_minus)
		fdf->zoom.key_out = 1;
	return (0);
}

int	key_release_handler(int keysym, t_fdf *fdf)
{
	if (keysym == XK_plus)
		fdf->zoom.key_in = 0;
	else if (keysym == XK_minus)
		fdf->zoom.key_out = 0;
	return (0);
}

int	loop_handler(t_fdf *fdf)
{
	if (fdf->zoom.key_in && fdf->zoom.key_out)
		return (0);
	else if (fdf->zoom.key_in)
		zoom_center(fdf, fdf->zoom.value * fdf->zoom.factor);
	else if (fdf->zoom.key_out)
		zoom_center(fdf, fdf->zoom.value / fdf->zoom.factor);
	return (0);
}
