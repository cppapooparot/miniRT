/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:38:34 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:26:20 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_rgb	calculate_ambient(t_scene *scene, t_hit_record *record)
{
	t_rgb	ambient_color;

	ambient_color = rgb_multiply(scene->ambient_light, record->color);
	ambient_color = rgb_scale(ambient_color, scene->ambient_intensity);
	return (ambient_color);
}

static t_rgb	calculate_diffuse(t_light *light, t_hit_record *record)
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

static bool	is_in_shadow(t_scene *scene, t_hit_record *record, t_light *light)
{
	t_ray			shadow_ray;
	t_hit_record	shadow_record;
	t_vec3			to_light;
	double			light_distance;

	to_light = vec3_subtract(light->position, record->point);
	light_distance = vec3_length(to_light);
	shadow_ray.origin = vec3_add(record->point, vec3_scale(record->normal,
				SHADOW_EPSILON));
	shadow_ray.direction = vec3_normalize(to_light);
	if (find_closest_intersection(shadow_ray, scene, &shadow_record))
		if (shadow_record.t < light_distance - SHADOW_EPSILON)
			return (true);
	return (false);
}

t_rgb	calculate_light(t_scene *scene, t_hit_record *record)
{
	t_rgb	final_color;
	t_list	*lights;
	t_light	*light;

	lights = scene->lights;
	final_color = calculate_ambient(scene, record);
	while (lights)
	{
		light = (t_light *)lights->content;
		if (!is_in_shadow(scene, record, light))
			final_color = rgb_add(final_color, calculate_diffuse(light,
						record));
		lights = lights->next;
	}
	return (rgb_clamp(final_color));
}
