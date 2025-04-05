/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:27:54 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/05 17:28:28 by migugar2         ###   ########.fr       */
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
