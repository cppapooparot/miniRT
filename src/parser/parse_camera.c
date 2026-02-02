/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:20:14 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/03 02:26:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static bool	parse_camera_args(char **tokens, t_scene *scene) {
  if (!parse_vec3(tokens[1], &scene->camera->position))
    return (false);
  if (!parse_vec3(tokens[2], &scene->camera->direction))
    return (false);
  if (!check_range_vec3(scene->camera->direction, -1.0, 1.0))
    return (put_error("Camera dir vector must be in range [-1,1]\n"));
  if (vec3_length(scene->camera->direction) < 0.0001)
    return (put_error("Direction cannot be zero\n"));
  scene->camera->direction = vec3_normalize(scene->camera->direction);
  if (!check_integer(tokens[3]))
    return (put_error("Invalid FOV\n"));
  scene->camera->fov = ft_atoi(tokens[3]);
  if (!check_ranged(scene->camera->fov, 0, 180))
    return (put_error("Camera FOV must be in range [0, 180]\n"));
  return (true);
}

bool	parse_camera(char **tokens, t_scene *scene) {
  if (scene->camera)
    return (put_error("Multiple cameras defined\n"));
  scene->camera = ft_calloc(1, sizeof(t_camera));
  if (!scene->camera)
    return (perror("Memory allocation failed\n"), false);
  if (!check_split_length(tokens, 4))
    return (put_error("Invalid camera definition\n"));
  if (!parse_camera_args(tokens, scene))
    return (false);
  return (true);
}
