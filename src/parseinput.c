/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:43:14 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/25 23:45:48 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

t_list	*read_file(int fd)
{
	t_list	*head;
	t_list	*current;
	char	*line;
	ssize_t	bytes_read;

	head = NULL;
	current = NULL;
	line = NULL;
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (ft_printf_error("Error file read\n"),
				ft_freestr(&line), ft_lstclear(&head, free), NULL);
		if (bytes_read == 0)
			break ;
		current = ft_lstnew(line);
		if (current == NULL)
			return (ft_printf_error("Error malloc\n"),
				ft_freestr(&line), ft_lstclear(&head, free), NULL);
		ft_lstadd_back(&head, current);
	}
	return (head);
}

t_color	parse_color(char *value)
{
	t_color	color;
	size_t	len;

	color = color_argb(255, 255, 255, 255);
	if (value == NULL)
		return (color);
	value++;
	len = 0;
	while (*value && value[len + 2] && value[len + 2] != ' ')
		len++;
	if (len == 6)
		color = color_argb(255, hex_to_dec(value + 2, 2),
				hex_to_dec(value + 4, 2), hex_to_dec(value + 6, 2));
	else if (len == 4)
		color = color_argb(255, 0, hex_to_dec(value + 2, 2),
				hex_to_dec(value + 4, 2));
	else if (len == 2)
		color = color_argb(255, 0, 0, hex_to_dec(value + 2, 2));
	else if (len == 3)
		color = color_argb(255, hexchar_to_dec(value[2]),
				hexchar_to_dec(value[3]), hexchar_to_dec(value[4]));
	return (color);
}

size_t	parse_value(t_fdf *fdf, char *value, float index, float count)
{
	long long	z_ll;
	size_t		val_len;
	t_vertex	point;
	char		*comma;
	float		space;

	val_len = is_valid_value(value);
	if (val_len == 0)
		return (ft_printf_error("Invalid .fdf file format\n"), 0);
	z_ll = ft_atoll(value);
	if (z_ll < -2147483648 || z_ll > 2147483647)
		return (ft_printf_error("Invalid .fdf file format\n"), 0);
	space = 10.0f;
	point.coord.x = index * space;
	point.coord.y = (count - 1) * space;
	point.coord.z = (float)z_ll;
	comma = ft_strchr(value, ',');
	if (comma != NULL)
		point.color = parse_color(comma);
	else
		point.color = color_argb(255, 255, 255, 255);
	if (ft_dynarradd(fdf->points.buffer, &point) == 0)
		return (ft_printf_error("Error malloc\n"), 0);
	return (val_len);
}

int	parse_line(t_fdf *fdf, char *line, int index)
{
	size_t	i;
	size_t	count;
	size_t	val_len;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			if (++count > fdf->points.line_length && index != 0)
				return (ft_printf_error("Invalid .fdf file format\n"), 1);
			val_len = parse_value(fdf, &line[i], index, count);
			if (val_len == 0)
				return (1);
			i += val_len - 1;
		}
		i++;
	}
	fdf->points.lines++;
	if (index == 0)
		fdf->points.line_length = count;
	else if (count != fdf->points.line_length)
		return (ft_printf_error("Invalid .fdf file format\n"), 1);
	return (0);
}

int	parse_input(t_fdf *fdf, char *filename)
{
	int		fd;
	t_list	*file;
	t_list	*current;

	if (!is_valid_filename(filename))
		return (ft_printf_error("Invalid file name\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf_error("Error file open\n"), 1);
	file = read_file(fd);
	if (file == NULL && (ft_close(&fd) || 1))
		return (1);
	fdf->points.buffer = ft_dynarrinit(128, sizeof(t_vertex));
	if (fdf->points.buffer == NULL)
		return (ft_lstclear(&file, free), 1);
	fdf->points.lines = 0;
	current = file;
	while (current != NULL)
	{
		if (parse_line(fdf, current->content, fdf->points.lines))
			return (ft_dynarrfree(&fdf->points.buffer, NULL),
				ft_lstclear(&file, free), 1);
		current = current->next;
	}
	return (ft_lstclear(&file, free), 0);
}
