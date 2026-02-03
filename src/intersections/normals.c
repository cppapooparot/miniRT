/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:42:48 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:26:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_vec3	face_forward(t_vec3 n, t_vec3 ray_dir)
{
	if (vec3_dot(n, ray_dir) > 0.0)
		return (vec3_scale(n, -1.0));
	return (n);
}

t_vec3	get_plane_normal(t_plane *plane, t_vec3 point, t_vec3 ray_dir)
{
	(void)point;
	return (face_forward(vec3_normalize(plane->normal), ray_dir));
}

t_vec3	get_sphere_normal(t_sphere *sphere, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	normal;

	normal = vec3_subtract(point, sphere->center);
	return (face_forward(vec3_normalize(normal), ray_dir));
}

t_vec3	get_cylinder_normal(t_cylinder *cylinder, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	normal;
	t_vec3	center_to_point;
	double	proj_length;

	center_to_point = vec3_subtract(point, cylinder->center);
	proj_length = vec3_dot(center_to_point, cylinder->axis);
	if (fabs(proj_length) >= (cylinder->height / 2))
	{
		if (proj_length > 0)
			return (face_forward(vec3_normalize(cylinder->axis), ray_dir));
		else
			return (face_forward(vec3_normalize(vec3_scale(cylinder->axis, -1)),
					ray_dir));
	}
	normal = vec3_subtract(center_to_point, vec3_scale(cylinder->axis,
				proj_length));
	return (face_forward(vec3_normalize(normal), ray_dir));
}
