/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:27:37 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/02 02:05:00 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/vec3d.h"

t_vec3	vec3_normalize(t_vec3 a)
{
	double	length;

	length = vec3_length(a);
	if (length < EPSILON)
		return ((t_vec3){0, 0, 0});
	return (vec3_div(a, length));
}

double	vec3_distance(t_vec3 a, t_vec3 b)
{
	t_vec3	diff;

	diff = vec3_subtract(a, b);
	return (vec3_length(diff));
}

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	double	dot;

	dot = vec3_dot(incident, normal);
	return (vec3_subtract(incident, vec3_scale(normal, 2.0 * dot)));
}
