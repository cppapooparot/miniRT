/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:38:34 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/31 19:46:25 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/intersections.h"

t_rgb	calculate_ambient(t_scene *scene, t_hit_record *record)
{
	t_rgb	ambient_color;

	ambient_color = rgb_multiply(scene->ambient_light, record->color);
	ambient_color = rgb_scale(ambient_color, scene->ambient_intensity);
	return (ambient_color);
}

t_rgb	calculate_diffuse(t_light *light, t_hit_record *record)
{
	t_vec3	light_dir;
	double	diffuse_intensity;
	t_rgb	diffuse_color;

	light_dir = vec3_normalize(vec3_subtract(light->position, record->point));
	diffuse_intensity = fmax(0.0, vec3_dot(record->normal, light_dir));
	diffuse_color = rgb_multiply(light->color, record->color);
	diffuse_color = rgb_scale(diffuse_color, diffuse_intensity
			* light->brightness);
	return (diffuse_color);
}

t_rgb	calculate_light(t_scene *scene, t_hit_record *record)
{
	t_rgb final_color;
	t_list *lights = scene->lights;

	final_color = calculate_ambient(scene, record);
	while (lights)
	{
		t_light *light = (t_light *)lights->content;
		final_color = rgb_add(final_color, calculate_diffuse(light, record));
		lights = lights->next;
	}
	return (rgb_clamp(final_color));
}