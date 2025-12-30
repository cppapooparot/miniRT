/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:27:02 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 15:02:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3d.h"

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

#endif