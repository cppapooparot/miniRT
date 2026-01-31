/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:38:34 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/30 01:15:13 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/scene.h"
#include "../../inc/vec3d.h"

t_rgb	calculate_ambient(t_scene *scene, t_rgb object_color)
{
	t_rgb	ambient_color;

	ambient_color = rgb_multiply(scene->ambient_light, object_color);
	ambient_color = rgb_scale(ambient_color, scene->ambient_intensity);
	return (ambient_color);
}
