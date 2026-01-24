/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:08:23 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/24 18:53:10 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, double scalar);
t_vec3		vec3_div(t_vec3 a, double scalar);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
double		vec3_length(t_vec3 a);
double		vec3_length_squared(t_vec3 a);
t_vec3		vec3_normalize(t_vec3 a);
double		vec3_distance(t_vec3 a, t_vec3 b);
t_vec3		vec3_reflect(t_vec3 v, t_vec3 n);

t_rgb		rgb_add(t_rgb a, t_rgb b);
t_rgb		rgb_scale(t_rgb color, double scalar);
t_rgb		rgb_multiply(t_rgb a, t_rgb b);
t_rgb		rgb_clamp(t_rgb color);
int			rgb_to_int(t_rgb color);

#endif