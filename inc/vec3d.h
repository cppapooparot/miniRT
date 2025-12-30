/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:08:23 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/29 16:09:22 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
#define VEC3D_H

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
} t_rgb;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

#endif