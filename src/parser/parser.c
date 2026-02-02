/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:19:45 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:26:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_parse_fn	get_parser(char *identifier)
{
	if (ft_strcmp(identifier, "A") == 0)
		return (parse_ambient_light);
	else if (ft_strcmp(identifier, "C") == 0)
		return (parse_camera);
	else if (ft_strcmp(identifier, "L") == 0)
		return (parse_light);
	else if (ft_strcmp(identifier, "sp") == 0)
		return (parse_sphere);
	else if (ft_strcmp(identifier, "pl") == 0)
		return (parse_plane);
	else if (ft_strcmp(identifier, "cy") == 0)
		return (parse_cylinder);
	return (NULL);
}

static bool	check_trim(char *line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (true);
	}
	free(trimmed_line);
	return (false);
}

static bool	parse_line(char *line, t_scene *scene)
{
	char		**line_tokens;
	t_parse_fn	parser;
	bool		result;

	line_tokens = ft_split(line, ' ');
	if (!line_tokens || !line_tokens[0])
	{
		ft_free_array((void ***)&line_tokens);
		return (put_error("Empty line or invalid format\n"));
	}
	if (check_trim(line_tokens[0]))
		return (ft_free_array((void ***)&line_tokens), true);
	if (line_tokens[0][0] == '#')
		return (ft_free_array((void ***)&line_tokens), true);
	parser = get_parser(line_tokens[0]);
	if (!parser)
	{
		ft_free_array((void ***)&line_tokens);
		return (put_error("Unknown identifier\n"));
	}
	result = parser(line_tokens, scene);
	ft_free_array((void ***)&line_tokens);
	return (result);
}

bool	read_file(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!check_file_extension(filename))
		return (put_error("File must have .rt extension\n"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), false);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
			return (free(line), close(fd), false);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
