/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:01:17 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:29:41 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_rgb	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit_record	record;

	if (!find_closest_intersection(ray, scene, &record))
		return ((t_rgb){0, 0, 0});
	return (calculate_light(scene, &record));
}

void	tracer_loop(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	int		pixel_color;

	data->scene.viewport = setup_viewport(data->scene.camera, data->mlx.width,
			data->mlx.height);
	x = -1;
	while (++x < data->mlx.width)
	{
		y = -1;
		while (++y < data->mlx.height)
		{
			ray = generate_ray(data, x, y);
			pixel_color = rgb_to_int(trace_ray(&data->scene, ray));
			mlx_put_pixel(&data->mlx, x, y, pixel_color);
		}
	}
}
