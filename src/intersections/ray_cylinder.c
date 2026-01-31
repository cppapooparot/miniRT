#include "../../inc/intersections.h"
#include <math.h>

static t_vec3   project_on_axis(t_vec3 v, t_vec3 axis)
{
    return (vec3_scale(axis, vec3_dot(v, axis)));
}

static bool intersect_disk(t_ray ray, ...);

bool intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
    double  radius;
    double  half_height;
    t_vec3  axis;
    t_vec3  oc;
}