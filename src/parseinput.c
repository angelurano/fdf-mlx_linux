/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:43:14 by migugar2          #+#    #+#             */
/*   Updated: 2025/04/24 01:33:53 by migugar2         ###   ########.fr       */
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
	len = 0;
	while (value[len + 2] && value[len + 2] != ' ')
		len++;
	if (len == 6)
		color = color_argb(255, hex_to_dec(value, 2),
				hex_to_dec(value + 2, 2), hex_to_dec(value + 4, 2));
	else if (len == 4)
		color = color_argb(255, 0, hex_to_dec(value, 2),
				hex_to_dec(value + 2, 2));
	else if (len == 2)
		color = color_argb(255, 0, 0, hex_to_dec(value, 2));
	else if (len == 3)
		color = color_argb(255, hexchar_to_dec(value[0]),
				hexchar_to_dec(value[1]), hexchar_to_dec(value[2]));
	return (color);
}

size_t	parse_value(t_fdf *fdf, char *value, float x, float y)
{
	long long	z_ll;
	size_t		val_len;
	t_vertex	point;
	char		*comma;

	val_len = is_valid_value(value);
	if (val_len == 0)
		return (ft_printf_error("Invalid .fdf file format\n"), 0);
	z_ll = ft_atoll(value);
	if (z_ll < -2147483648 || z_ll > 2147483647)
		return (ft_printf_error("Invalid .fdf file format\n"), 0);
	point.coord = (t_vec3){x, y, (float)z_ll};
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

/*
int	parse_line(t_fdf *fdf, char *line)
{

	char	**split;
	size_t	i;
	t_point	*points;

	// Bad format map error: "Invalid .fdf file format"
	// TODO: Check if the line has the same number of elements with a function of checkinput.c
	// TODO: Finally check if points lines is more than 0
	// TODO: Check for each point if the values are valid, in my case, I will check if the values are numbers, af i we got a color too (split(",")), check if the value is hexadecimal (0x)
}

int	read_file(t_fdf *fdf, char *filename)
{
	int			fd;
	char		*line;
	ssize_t		bytes_read;
	char		*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || ft_strcmp(dot, ".fdf") != 0)
		return (ft_printf_error("Invalid file extension\n"), 1);

	if (fd == -1)
		return (ft_printf_error("Error opening file\n"), 1);
	line = NULL;
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (ft_printf_error("Error reading file\n"),
				ft_freestr(&line), close(fd), 1);
		if (bytes_read == 0)
			break ;
		if (parse_line(fdf, line))
			return (ft_freestr(&line), close(fd), 1);
		ft_freestr(&line);
	}
	return (ft_freestr(&line), close(fd), 0);
}
*/
