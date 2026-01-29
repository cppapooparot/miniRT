/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:07:51 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/27 20:28:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/scene.h"

t_viewport	setup_viewport(t_camera *camera, int image_width, int image_height)
{
	t_viewport	viewport;
	t_basis		camera_basis;
	double		aspect_ratio;
	t_vec3		up;

	up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(camera->direction.y) > 0.999)
		up = (t_vec3){1.0, 0.0, 0.0};
	aspect_ratio = (double)image_width / (double)image_height;
	viewport.focal_length = 1.0;
	viewport.height = 2.0 * tan((camera->fov * 0.5) * (M_PI / 180.0));
	viewport.width = aspect_ratio * viewport.height;
	camera_basis.w = vec3_negate(camera->direction);
	camera_basis.u = vec3_normalize(vec3_cross(up, camera_basis.w));
	camera_basis.v = vec3_cross(camera_basis.w, camera_basis.u);
	viewport.horizontal = vec3_scale(camera_basis.u, viewport.width);
	viewport.vertical = vec3_scale(camera_basis.v, viewport.height);
	viewport.center = vec3_add(camera->position, vec3_scale(camera->direction,
				viewport.focal_length));
	viewport.upper_left = viewport.center;
	viewport.upper_left = vec3_subtract(viewport.upper_left,
			vec3_scale(viewport.horizontal, 0.5));
	viewport.upper_left = vec3_subtract(viewport.upper_left,
			vec3_scale(viewport.vertical, 0.5));
	return (viewport);
}

t_ray	generate_ray(t_data *data, int x, int y)
{
	t_ray	ray;
	double	u;
	double	v;
	t_vec3	pixel;

	u = (x + 0.5) / data->mlx.width;
	v = (y + 0.5) / data->mlx.height;
	pixel = data->scene.viewport.upper_left;
	pixel = vec3_add(pixel, vec3_scale(data->scene.viewport.horizontal, u));
	pixel = vec3_add(pixel, vec3_scale(data->scene.viewport.vertical, v));
	ray.origin = data->scene.camera->position;
	ray.direction = vec3_normalize(vec3_subtract(pixel,
				data->scene.camera->position));
	return (ray);
}
