/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:15:26 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 19:15:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	initialize_scene(char *filename, t_scene *scene)
{
	scene->ambient_intensity = 0.0;
	scene->ambient_light = (t_rgb){0, 0, 0};
	scene->camera = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	if (!read_file(filename, scene))
		return (false);
	return (true);
}
