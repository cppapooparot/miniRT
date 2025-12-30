/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:06:15 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 19:21:23 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "objects.h"
# include "vec3d.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_scene
{
	t_rgb		ambient_light;
	double		ambient_intensity;
	t_camera	*camera;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}				t_scene;

typedef bool	(*t_parse_fn)(char **, t_scene *);

/* VALIDATE */
bool			check_file_extension(char *filename);
bool			check_double(const char *str);
bool			check_integer(const char *str);
bool			check_rgb_values(int r, int g, int b);
bool			check_split_length(char **tokens, int expected_length);
bool			check_arg_format(char **tokens, int expected_length,
					bool (*check_func)(const char *));
bool			check_ranged(double value, double min, double max);
bool			check_range_vec3(t_vec3 vec, double min, double max);

/* UTILS */
bool			put_error(char *message);

/* INITIALIZE */
bool			initialize_scene(char *filename, t_scene *scene);
bool			read_file(char *filename, t_scene *scene);
bool			parse_ambient_light(char **tokens, t_scene *scene);
bool			parse_camera(char **tokens, t_scene *scene);
bool			parse_light(char **tokens, t_scene *scene);
bool			parse_sphere(char **tokens, t_scene *scene);
bool			parse_plane(char **tokens, t_scene *scene);
bool			parse_cylinder(char **tokens, t_scene *scene);
bool			parse_vec3(char *str, t_vec3 *vec);
bool			parse_rgb(char *str, t_rgb *color);

#endif