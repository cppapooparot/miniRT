#include "../../inc/intersections.h"
#include <math.h>

static t_vec3   project_on_axis(t_vec3 v, t_vec3 axis)
{
    return (vec3_scale(axis, vec3_dot(v, axis)));
}

static bool intersect_disk(t_ray ray, t_vec3 disk_center, t_vec3 disk_normal, double radius, double *t_hit)
{
    double denom;
    double t;
    t_vec3 p;
    t_vec3 v;
    t_vec3 in_plane;
    double dist_square;

    if (!t_hit)
        return (false);
    denom = vec3_dot(ray.direction, disk_normal);
    if (fabs(denom) < EPSILON)
        return (false);
    t = vec3_dot(vec3_subtract(disk_center, ray.origin), disk_normal) / denom;
    if (t < EPSILON)
        return (false);
    p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
    v = vec3_subtract(p, disk_center);
    in_plane = vec3_subtract(v, project_on_axis(v, disk_normal));
    dist_square = vec3_length_squared(in_plane);
    if (dist_square > radius * radius)
        return (false);
    *t_hit = t;
    return (true);
}

bool intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
    double  radius;
    double  half_height;
    t_vec3  axis;
    t_vec3  oc;
    
    return (true);
}