/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:20:14 by nsahakya          #+#    #+#             */
/*   Updated: 2026/02/06 18:20:16 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
	double	t_body;
	double	t_disk;
	bool	hit_body;
	bool	hit_disk;

	if (!cylinder || !t)
		return (false);
	if (cylinder->radius <= 0.0 || cylinder->half_height <= 0.0)
		return (false);
	hit_body = cylinder_body_hit(ray, cylinder, &t_body);
	hit_disk = cylinder_disk_hit(ray, cylinder, &t_disk);
	if (!hit_body && !hit_disk)
		return (false);
	if (hit_body && (!hit_disk || t_body < t_disk))
		*t = t_body;
	else
		*t = t_disk;
	return (true);
}
