/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:19:45 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 16:07:13 by maghumya         ###   ########.fr       */
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
		return (NULL); // parse_light);
	else if (ft_strcmp(identifier, "sp") == 0)
		return (NULL); // parse_sphere);
	else if (ft_strcmp(identifier, "pl") == 0)
		return (NULL); // parse_plane);
	else if (ft_strcmp(identifier, "cy") == 0)
		return (NULL); // parse_cylinder);
	return (NULL);
}

bool	read_file(char *filename, t_scene *scene)
{
	int			fd;
	char		*line;
	char		**line_tokens;
	t_parse_fn	parser;

	if (!check_file_extension(filename))
		return (put_error("File must have .rt extension\n"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), false);
	line = get_next_line(fd);
	while (line)
	{
		line_tokens = ft_split(line, ' ');
		if (!line_tokens || !line_tokens[0])
		{
			free(line);
			ft_free_array((void ***)&line_tokens);
			close(fd);
			return (false);
		}
		parser = get_parser(line_tokens[0]);
		if (parser && !parser(line_tokens, scene))
		{
			free(line);
			ft_free_array((void ***)&line_tokens);
			close(fd);
			return (false);
		}
		printf("%s", line);
		free(line);
		ft_free_array((void ***)&line_tokens);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
