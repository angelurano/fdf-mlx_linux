/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:27:54 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/09 23:56:06 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	key_release_handler(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Up)
		fdf->input.key_up = 0;
	else if (keysym == XK_Down)
		fdf->input.key_down = 0;
	else if (keysym == XK_Left)
		fdf->input.key_left = 0;
	else if (keysym == XK_Right)
		fdf->input.key_right = 0;
	return (0);
}

int	key_press_handler(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		return (close_handler(fdf));
	if (keysym == XK_Up)
		fdf->input.key_up = 1;
	else if (keysym == XK_Down)
		fdf->input.key_down = 1;
	else if (keysym == XK_Left)
		fdf->input.key_left = 1;
	else if (keysym == XK_Right)
		fdf->input.key_right = 1;
	return (0);
}

int	loop_handler(t_fdf *fdf)
{
	int	must_render; // TODO: remove this variable, use a flag or something instead

	must_render = 0;
	if (fdf->input.key_up)
	{
		fdf->camera.offset.y -= 10;
		must_render = 1;
	}
	if (fdf->input.key_down)
	{
		fdf->camera.offset.y += 10;
		must_render = 1;
	}
	if (fdf->input.key_left)
	{
		fdf->camera.offset.x -= 10;
		must_render = 1;
	}
	if (fdf->input.key_right)
	{
		fdf->camera.offset.x += 10;
		must_render = 1;
	}
	if (must_render)
		render(fdf);
	return (0);
}

int	close_handler(t_fdf *fdf)
{
	free(fdf->framebuffer);
	mlx_destroy_window(fdf->connection, fdf->window);
	mlx_destroy_image(fdf->connection, fdf->img.img_ptr);
	mlx_destroy_display(fdf->connection);
	free(fdf->connection);
	ft_dynarrfree(&fdf->points.buffer, NULL);
	exit(0);
	return (0);
}
