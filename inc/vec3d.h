/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:08:23 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:24:39 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

# ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES
# endif

# include <math.h>

# define EPSILON 1e-6
# define SHADOW_EPSILON 1e-4

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_basis
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}			t_basis;

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

/* OBJECTS */

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_rgb	color;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3 normal; // MUST be normalized
	t_rgb	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3 axis; // MUST be normalized
	double	diameter;
	double	height;
	t_rgb	color;
}			t_cylinder;

typedef struct s_light
{
	t_vec3	position;
	double brightness; // [0.0, 1.0]
	t_rgb	color;
}			t_light;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3 direction; // MUST be normalized
	int fov;          // Field of view (degrees)
}			t_camera;

t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, double scalar);
t_vec3		vec3_div(t_vec3 a, double scalar);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
t_vec3		vec3_negate(t_vec3 a);
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