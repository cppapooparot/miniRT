/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:42:48 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/31 16:44:03 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/objects.h"
#include "../../inc/scene.h"
#include "../../inc/vec3d.h"

t_vec3	get_plane_normal(t_plane *plane, t_vec3 point)
{
	(void)point;
	return (vec3_normalize(plane->normal));
}

t_vec3	get_sphere_normal(t_sphere *sphere, t_vec3 point)
{
	t_vec3	normal;

	normal = vec3_subtract(point, sphere->center);
	return (vec3_normalize(normal));
}

t_vec3	get_cylinder_normal(t_cylinder *cylinder, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	center_to_point;
	double	proj_length;

	center_to_point = vec3_subtract(point, cylinder->center);
	proj_length = vec3_dot(center_to_point, cylinder->axis);
	if (fabs(proj_length) >= (cylinder->height / 2))
	{
		if (proj_length > 0)
			return (vec3_normalize(cylinder->axis));
		else
			return (vec3_normalize(vec3_scale(cylinder->axis, -1)));
	}
	normal = vec3_subtract(center_to_point, vec3_scale(cylinder->axis,
				proj_length));
	return (vec3_normalize(normal));
}
