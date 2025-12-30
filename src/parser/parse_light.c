/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:10:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 18:23:32 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	parse_ambient_light(char **tokens, t_scene *scene)
{
	if (!check_split_length(tokens, 3))
		return (put_error("Invalid ambient light definition\n"));
	if (!check_double(tokens[1]))
		return (put_error("Invalid ambient light intensity\n"));
	scene->ambient_intensity = atof(tokens[1]);
	if (!check_ranged(scene->ambient_intensity, 0.0, 1.0))
		return (put_error("Light brightness must be in range [0,1]\n"));
	if (!parse_rgb(tokens[2], &scene->ambient_light))
		return (false);
	return (true);
}

bool	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;
	t_list	*new_light_node;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (perror("Memory allocation failed\n"), false);
	if (!check_split_length(tokens, 4))
		return (free(light), put_error("Invalid light definition\n"));
	if (!parse_vec3(tokens[1], &light->position))
		return (free(light), false);
	if (!check_double(tokens[2]))
		return (free(light), put_error("Invalid light brightness\n"));
	light->brightness = ft_atod(tokens[2]);
	if (!check_ranged(light->brightness, 0.0, 1.0))
		return (free(light),
			put_error("Light brightness must be in range [0,1]\n"));
	if (!parse_rgb(tokens[3], &light->color))
		return (free(light), false);
	new_light_node = ft_lstnew(light);
	if (!new_light_node)
		return (perror("Memory allocation failed\n"), free(light), false);
	ft_lstadd_back(&scene->lights, new_light_node);
	return (true);
}
