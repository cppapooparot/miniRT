/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:06:52 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 19:52:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;
	t_list		*new_sphere_node;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("Memory allocation failed\n"), false);
	if (!check_split_length(tokens, 4))
		return (free(sphere), put_error("Invalid sphere definition\n"));
	if (!parse_vec3(tokens[1], &sphere->center))
		return (free(sphere), false);
	if (!check_double(tokens[2]))
		return (free(sphere), put_error("Invalid sphere diameter\n"));
	sphere->radius = ft_atod(tokens[2]) / 2.0;
	if (sphere->radius <= 0)
		return (put_error("Sphere radius must be positive\n"));
	if (!parse_rgb(tokens[3], &sphere->color))
		return (free(sphere), false);
	new_sphere_node = ft_lstnew(sphere);
	if (!new_sphere_node)
		return (perror("Memory allocation failed\n"), free(sphere), false);
	ft_lstadd_back(&scene->spheres, new_sphere_node);
	return (true);
}

bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;
	t_list	*new_plane_node;

	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (perror("Memory allocation failed\n"), false);
	if (!check_split_length(tokens, 4))
		return (free(plane), put_error("Invalid plane definition\n"));
	if (!parse_vec3(tokens[1], &plane->point))
		return (free(plane), false);
	if (!parse_vec3(tokens[2], &plane->normal))
		return (free(plane), false);
	if (!check_range_vec3(plane->normal, -1.0, 1.0))
		return (free(plane),
			put_error("Plane normal vector must be in range [-1,1]\n"));
	if (!parse_rgb(tokens[3], &plane->color))
		return (free(plane), false);
	new_plane_node = ft_lstnew(plane);
	if (!new_plane_node)
		return (perror("Memory allocation failed\n"), free(plane), false);
	ft_lstadd_back(&scene->planes, new_plane_node);
	return (true);
}

static bool	parse_cylinder_args(char **tokens, t_cylinder *cylinder)
{
	if (!parse_vec3(tokens[1], &cylinder->center))
		return (false);
	if (!parse_vec3(tokens[2], &cylinder->axis))
		return (false);
	if (!check_range_vec3(cylinder->axis, -1.0, 1.0))
		return (put_error("Cylinder axis vector must be in range [-1,1]\n"));
	if (!check_double(tokens[3]) || !check_double(tokens[4]))
		return (put_error("Invalid cylinder dimensions\n"));
	cylinder->diameter = ft_atod(tokens[3]);
	cylinder->height = ft_atod(tokens[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (put_error("Cylinder diameter and height must be positive\n"));
	if (!parse_rgb(tokens[5], &cylinder->color))
		return (false);
	return (true);
}

bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_list		*new_cylinder_node;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (perror("Memory allocation failed\n"), false);
	if (!check_split_length(tokens, 6))
		return (free(cylinder), put_error("Invalid cylinder definition\n"));
	if (!parse_cylinder_args(tokens, cylinder))
		return (free(cylinder), false);
	new_cylinder_node = ft_lstnew(cylinder);
	if (!new_cylinder_node)
		return (perror("Memory allocation failed\n"), free(cylinder), false);
	ft_lstadd_back(&scene->cylinders, new_cylinder_node);
	return (true);
}
